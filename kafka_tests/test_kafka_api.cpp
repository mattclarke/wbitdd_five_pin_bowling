#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include <chrono>
#include <memory>
#include <set>
#include <string>
#include <utility>

#include <unistd.h>

#include <fmt/format.h>

#include "kafka_consumer.h"
#include "kafka_producer.h"

std::string create_unique_group_id() {
  // If the group ID is not unique then a consumer will join at the last
  // recorded offset for that ID. The offset for the ID is stored in Kafka.
  return fmt::format("tests-{}--time:{}", getpid(),
                     std::chrono::duration_cast<std::chrono::milliseconds>(
                         std::chrono::steady_clock::now().time_since_epoch())
                         .count());
}

TEST_CASE("produce and consume one message on topic", "[kafka]") {
  const std::string topic = "test_topic";
  const std::string broker = "localhost:9092";

  auto consumer = KafkaConsumer(broker, create_unique_group_id());
  consumer.subscribe({topic});
  // subscribe is asynchronous but "consume" will block until it connects.
  // note from future matt: if there are no messages then this will block forever!
  [[maybe_unused]] auto ignore = consumer.consume_message();

  auto producer = KafkaProducer(broker);
  const std::string sent_message = fmt::format("Hello{}", rand());
  producer.send_message(topic, sent_message);

  std::string received_message = consumer.consume_message();
  while (received_message.empty()) {
    received_message = consumer.consume_message();
  }

  REQUIRE(received_message == sent_message);
}

TEST_CASE("produce and consume multiple messages on a topic", "[kafka]") {
  // Using sets as Kafka offers no order guarantees.
  // As we are using a single partition the chances of a message being out of
  // order are very slim, but...
  const int num_messages = 10;
  const std::string topic = "test_topic";
  const std::string broker = "localhost:9092";

  auto consumer = KafkaConsumer(broker, create_unique_group_id());
  consumer.subscribe({topic});
  // subscribe is asynchronous but "consume" will block until it connects.
  [[maybe_unused]] auto ignore = consumer.consume_message();

  auto producer = KafkaProducer(broker);
  std::set<std::string, std::less<>> sent_messages;
  for (int i = 0; i < num_messages; ++i) {
    const std::string sent_message = fmt::format("Hello{}", rand());
    sent_messages.insert(sent_message);
    producer.send_message(topic, sent_message);
  }

  std::set<std::string, std::less<>> received_messages;
  for (int i = 0; i < num_messages; ++i) {
    received_messages.insert(consumer.consume_message());
  }

  REQUIRE(received_messages == sent_messages);
}
