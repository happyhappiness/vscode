static derive_t float_counter_get(const float_counter_t *fc, /* {{{ */
                                  uint64_t factor) {
  derive_t ret;

  ret = (derive_t)(fc->i * factor);
  ret += (derive_t)(fc->n / (1000000000 / factor));

  return (ret);
}