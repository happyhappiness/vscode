static int verify_sha256(void *payload, size_t payload_size,
                         char const *username, char const *password,
                         uint8_t hash_provided[32]) {
  return ENOTSUP;
}