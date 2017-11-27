static char *kafka_random_key(char buffer[static KAFKA_RANDOM_KEY_SIZE]) {
  snprintf(buffer, KAFKA_RANDOM_KEY_SIZE, "%08" PRIX32, cdrand_u());
  return buffer;
}