int parse_values(void *payload, size_t payload_size,
                        lcc_value_list_t *state) {
  buffer_t *b = &(buffer_t){
      .data = payload, .len = payload_size,
  };

  uint16_t n;
  if (buffer_uint16(b, &n))
    return EINVAL;

  if (((size_t)n * 9) != b->len)
    return EINVAL;

  state->values_len = (size_t)n;
  state->values = calloc(sizeof(*state->values), state->values_len);
  state->values_types = calloc(sizeof(*state->values_types), state->values_len);
  if ((state->values == NULL) || (state->values_types == NULL)) {
    return ENOMEM;
  }

  for (uint16_t i = 0; i < n; i++) {
    uint8_t tmp;
    if (buffer_next(b, &tmp, sizeof(tmp)))
      return EINVAL;
    state->values_types[i] = (int)tmp;
  }

  for (uint16_t i = 0; i < n; i++) {
    uint64_t tmp;
    if (buffer_next(b, &tmp, sizeof(tmp)))
      return EINVAL;

    if (state->values_types[i] == LCC_TYPE_GAUGE) {
      union {
        uint64_t i;
        double d;
      } conv = {.i = tmp};
      state->values[i].gauge = ntohd(conv.d);
      continue;
    }

    tmp = be64toh(tmp);
    switch (state->values_types[i]) {
    case LCC_TYPE_COUNTER:
      state->values[i].counter = (counter_t)tmp;
      break;
    case LCC_TYPE_DERIVE:
      state->values[i].derive = (derive_t)tmp;
      break;
    case LCC_TYPE_ABSOLUTE:
      state->values[i].absolute = (absolute_t)tmp;
      break;
    default:
      return EINVAL;
    }
  }

  return 0;
}