#ifndef KAFKA_PRODUCER_H
#define KAFKA_PRODUCER_H

#include <librdkafka/rdkafkacpp.h>
#include "kafka_exception.h"

class KafkaProducer {
public:
  explicit KafkaProducer(std::string broker) : broker_(std::move(broker)) {
    std::string errorMsg;

    auto config = std::unique_ptr<RdKafka::Conf>(
        RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
    if (config->set("bootstrap.servers", broker_, errorMsg) !=
        RdKafka::Conf::CONF_OK) {
      throw KafkaException(errorMsg);
    }

    producer_ = std::unique_ptr<RdKafka::Producer>(
        RdKafka::Producer::create(config.get(), errorMsg));
    if (producer_ == nullptr) {
      throw KafkaException(
          fmt::format("Failed to create producer: {}", errorMsg));
    }
  }

  void send_message(const std::string &topic, const std::string &message) {
    auto *buffer = new char[message.size() + 1];
    memcpy(buffer, message.c_str(), message.size() + 1);

    RdKafka::ErrorCode err = producer_->produce(
        topic, RdKafka::Topic::PARTITION_UA, RdKafka::Producer::RK_MSG_FREE,
        buffer, message.size(), nullptr, 0, 0, nullptr, nullptr);

    if (err != RdKafka::ERR_NO_ERROR) {
      throw KafkaException(
          fmt::format("Failed to produce to topic: {}", RdKafka::err2str(err)));
    }

    err = producer_->flush(1000);
    if (err != RdKafka::ERR_NO_ERROR) {
      throw KafkaException(
          fmt::format("Failed to flush: {}", RdKafka::err2str(err)));
    }
  }

private:
  std::string broker_;
  std::unique_ptr<RdKafka::Producer> producer_;
};

#endif // KAFKA_PRODUCER_H
