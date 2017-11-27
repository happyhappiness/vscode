cdtime_t plugin_get_interval(void) {
  cdtime_t interval;

  interval = plugin_get_ctx().interval;
  if (interval > 0)
    return interval;

  return cf_get_default_interval();
}