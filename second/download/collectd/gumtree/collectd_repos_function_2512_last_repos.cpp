static int parse_string(void *payload, size_t payload_size, char *out,
                        size_t out_size) {
  char *in = payload;

  if ((payload_size < 1) || (in[payload_size - 1] != 0) ||
      (payload_size > out_size))
    return EINVAL;

  strncpy(out, in, out_size);
  return 0;
}