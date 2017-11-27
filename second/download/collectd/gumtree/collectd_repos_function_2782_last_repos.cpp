cdtime_t cf_get_default_interval(void) {
  return global_option_get_time("Interval",
                                DOUBLE_TO_CDTIME_T(COLLECTD_DEFAULT_INTERVAL));
}