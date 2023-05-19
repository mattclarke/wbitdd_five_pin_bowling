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
> mkdir _ninja
> conan install . --output-folder=_ninja --build=missing
> cd _ninja
> cmake .. -GNinja -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake
> ninja && ./bin/test_kafka
```