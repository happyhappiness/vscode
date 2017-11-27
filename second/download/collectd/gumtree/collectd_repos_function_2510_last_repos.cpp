static int buffer_uint16(buffer_t *b, uint16_t *out) {
  uint16_t tmp;
  if (buffer_next(b, &tmp, sizeof(tmp)) != 0)
    return -1;

  *out = be16toh(tmp);
  return 0;
}