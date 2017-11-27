static char *kafka_random_key(char buffer[static KAFKA_RANDOM_KEY_SIZE]) {
  ssnprintf(buffer, KAFKA_RANDOM_KEY_SIZE, "%08lX", (unsigned long)mrand48());
  return buffer;
}