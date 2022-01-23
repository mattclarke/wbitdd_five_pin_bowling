# Kafka API tests

Tests that the Kafka API behaves as we expect.

From scratch
```
> docker compose up
> mkdir _ninja && cd _ninja
> conan install ..
> cmake -G Ninja ..
> ninja && ./bin/test_kafka
```