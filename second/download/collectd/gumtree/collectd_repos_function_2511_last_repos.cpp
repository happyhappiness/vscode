static int parse_int(void *payload, size_t payload_size, uint64_t *out) {
  uint64_t tmp;

  if (payload_size != sizeof(tmp))
    return EINVAL;

  memmove(&tmp, payload, sizeof(tmp));
  *out = be64toh(tmp);
  return 0;
}