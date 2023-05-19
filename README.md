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
> git clone https://github.com/microsoft/vcpkg
> ./vcpkg/bootstrap-vcpkg.sh
> ./vcpkg/vcpkg install librdkafka catch2 fmt
> mkdir _ninja
> cd _ninja
> cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release
> ninja && ./bin/test_kafka
```