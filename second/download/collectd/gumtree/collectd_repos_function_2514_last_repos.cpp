static int parse_time(uint16_t type, void *payload, size_t payload_size,
                      lcc_value_list_t *state) {
  uint64_t tmp = 0;
  if (parse_int(payload, payload_size, &tmp))
    return EINVAL;

  double t = (double)tmp;
  switch (type) {
  case TYPE_INTERVAL:
    state->interval = t;
    break;
  case TYPE_INTERVAL_HR:
    state->interval = t / 1073741824.0;
    break;
  case TYPE_TIME:
    state->time = t;
    break;
  case TYPE_TIME_HR:
    state->time = t / 1073741824.0;
    break;
  default:
    return EINVAL;
  }

  return 0;
}