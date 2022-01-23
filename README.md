# Five Pin Bowling

## kafka_tests

Tests that the Kafka API behaves as we expect.

From a terminal:
```
> cd kafka_tests
> docker compose up
```

From a second terminal:
```
> mkdir _ninja && cd _ninja
> conan install ..
> cmake -G Ninja ..
> ninja && ./bin/test_kafka
```