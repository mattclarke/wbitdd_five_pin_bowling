#ifndef KAFKA_CONSUMER_H
#define KAFKA_CONSUMER_H

#include <librdkafka/rdkafkacpp.h>
#include "kafka_exception.h"

class KafkaConsumer {
public:
  KafkaConsumer(std::string broker, std::string group_id)
      : broker_(std::move(broker)), group_id_(std::move(group_id)) {
    std::string errorMessage;

    auto config = std::unique_ptr<RdKafka::Conf>(
        RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
    if (config->set("bootstrap.servers", broker_, errorMessage) !=
        RdKafka::Conf::CONF_OK) {
      throw KafkaException(errorMessage);
    }

    if (config->set("group.id", group_id_, errorMessage) !=
        RdKafka::Conf::CONF_OK) {
      throw KafkaException(errorMessage);
    }

    if (config->set("auto.offset.reset", "largest", errorMessage) !=
        RdKafka::Conf::CONF_OK) {
      throw KafkaException(errorMessage);
    }

    consumer_ = std::unique_ptr<RdKafka::KafkaConsumer>(
        RdKafka::KafkaConsumer::create(config.get(), errorMessage));
    if (consumer_ == nullptr) {
      throw KafkaException(
          fmt::format("Failed to create consumer: {}", errorMessage));
    }
  }

  ~KafkaConsumer() noexcept {
    try {
      close();
    } catch (const std::exception &) {
      // Don't let an exception propagate out of a destructor.
    }
  }

  KafkaConsumer(KafkaConsumer &&other) noexcept = default;
  KafkaConsumer(const KafkaConsumer &other) = delete;
  KafkaConsumer &operator=(const KafkaConsumer &other) = delete;
  KafkaConsumer &operator=(KafkaConsumer &&other) noexcept = delete;

  void subscribe(const std::vector<std::string> &topics) const {
    RdKafka::ErrorCode err = consumer_->subscribe(topics);
    if (err != RdKafka::ERR_NO_ERROR) {
      throw KafkaException(fmt::format("Failed to subscribe to topic: {}",
                                       RdKafka::err2str(err)));
    }
  }

  [[nodiscard]] std::string consume_message() const {
    auto received = std::unique_ptr<RdKafka::Message>(consumer_->consume(1000));

    std::string received_message;
    if (received->payload() != nullptr) {
      auto payload = static_cast<const char *>(received->payload());
      const auto payloadSize = static_cast<int>(received->len());
      received_message = std::string(payload, payload + payloadSize);
    }

    return received_message;
  }

  void close() {
    if (!consumer_) {
      return;
    }

    if (auto err = consumer_->close(); err != RdKafka::ERR_NO_ERROR) {
      throw KafkaException(
          fmt::format("Could not close consumer: {}", RdKafka::err2str(err)));
    }
    consumer_.reset();
  }

private:
  const std::string broker_;
  const std::string group_id_;
  std::unique_ptr<RdKafka::KafkaConsumer> consumer_{nullptr};
};

#endif // KAFKA_CONSUMER_H
