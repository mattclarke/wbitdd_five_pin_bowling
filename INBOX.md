# Inbox

## TODO

- Kafka: more specific exceptions types
- Kafka: create producer class
- implement a scoring system walking skeleton
  - my plan: "server" tells "lane" to start a game, game acknowledges start and then returns score of 0
- score a game in progress
  - Fake pinsetter telling which pins are knocked down, misses, etc.
  - Events
  - assert/exception if more than 5 pins knocked down on a ball
  - same pin multiple times in a ball == error
  - dead ball (previous ball undo)
- basic display of score in recognised format
  - Use the slang terms
  - final score
  - updating score
  - add sanitisers?



## DONE
- Kafka: create API tests
- Kafka: create consumer wrapper
- Kafka: create custome exception
- Kafka: create producer class