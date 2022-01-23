#ifndef KAFKA_EXCEPTION_H
#define KAFKA_EXCEPTION_H

class KafkaException : public std::runtime_error {
public:
  using runtime_error::runtime_error;
};

#endif // KAFKA_EXCEPTION_H
