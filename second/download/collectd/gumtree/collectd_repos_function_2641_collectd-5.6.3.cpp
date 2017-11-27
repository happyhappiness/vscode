int
plugin_dispatch_multivalue(value_list_t const *template, /* {{{ */
                           _Bool store_percentage, int store_type, ...) {
  value_list_t *vl;
  int failed = 0;
  gauge_t sum = 0.0;
  va_list ap;

  assert(template->values_len == 1);

  /* Calculate sum for Gauge to calculate percent if needed */
  if (DS_TYPE_GAUGE == store_type) {
    va_start(ap, store_type);
    while (42) {
      char const *name;
      gauge_t value;

      name = va_arg(ap, char const *);
      if (name == NULL)
        break;

      value = va_arg(ap, gauge_t);
      if (!isnan(value))
        sum += value;
    }
    va_end(ap);
  }

  vl = plugin_value_list_clone(template);
  /* plugin_value_list_clone makes sure vl->time is set to non-zero. */
  if (store_percentage)
    sstrncpy(vl->type, "percent", sizeof(vl->type));

  va_start(ap, store_type);
  while (42) {
    char const *name;
    int status;

    /* Set the type instance. */
    name = va_arg(ap, char const *);
    if (name == NULL)
      break;
    sstrncpy(vl->type_instance, name, sizeof(vl->type_instance));

    /* Set the value. */
    switch (store_type) {
    case DS_TYPE_GAUGE:
      vl->values[0].gauge = va_arg(ap, gauge_t);
      if (store_percentage)
        vl->values[0].gauge *= sum ? (100.0 / sum) : NAN;
      break;
    case DS_TYPE_ABSOLUTE:
      vl->values[0].absolute = va_arg(ap, absolute_t);
      break;
    case DS_TYPE_COUNTER:
      vl->values[0].counter = va_arg(ap, counter_t);
      break;
    case DS_TYPE_DERIVE:
      vl->values[0].derive = va_arg(ap, derive_t);
      break;
    default:
      ERROR("plugin_dispatch_multivalue: given store_type is incorrect.");
      failed++;
    }

    status = plugin_write_enqueue(vl);
    if (status != 0)
      failed++;
  }
  va_end(ap);

  plugin_value_list_free(vl);
  return (failed);
}