static int values_to_kairosdb(char *buffer, size_t buffer_size, /* {{{ */
                              const data_set_t *ds, const value_list_t *vl,
                              int store_rates, size_t ds_idx) {
  size_t offset = 0;
  gauge_t *rates = NULL;

  memset(buffer, 0, buffer_size);

#define BUFFER_ADD(...)                                                        \
  do {                                                                         \
    int status;                                                                \
    status = snprintf(buffer + offset, buffer_size - offset, __VA_ARGS__);     \
    if (status < 1) {                                                          \
      sfree(rates);                                                            \
      return -1;                                                               \
    } else if (((size_t)status) >= (buffer_size - offset)) {                   \
      sfree(rates);                                                            \
      return -ENOMEM;                                                          \
    } else                                                                     \
      offset += ((size_t)status);                                              \
  } while (0)

  if (ds->ds[ds_idx].type == DS_TYPE_GAUGE) {
    if (isfinite(vl->values[ds_idx].gauge)) {
      BUFFER_ADD("[[");
      BUFFER_ADD("%" PRIu64, CDTIME_T_TO_MS(vl->time));
      BUFFER_ADD(",");
      BUFFER_ADD(JSON_GAUGE_FORMAT, vl->values[ds_idx].gauge);
    } else {
      DEBUG("utils_format_kairosdb: invalid vl->values[ds_idx].gauge for "
            "%s|%s|%s|%s|%s",
            vl->plugin, vl->plugin_instance, vl->type, vl->type_instance,
            ds->ds[ds_idx].name);
      return -1;
    }
  } else if (store_rates) {
    if (rates == NULL)
      rates = uc_get_rate(ds, vl);
    if (rates == NULL) {
      WARNING("utils_format_kairosdb: uc_get_rate failed for %s|%s|%s|%s|%s",
              vl->plugin, vl->plugin_instance, vl->type, vl->type_instance,
              ds->ds[ds_idx].name);

      return -1;
    }

    if (isfinite(rates[ds_idx])) {
      BUFFER_ADD("[[");
      BUFFER_ADD("%" PRIu64, CDTIME_T_TO_MS(vl->time));
      BUFFER_ADD(",");
      BUFFER_ADD(JSON_GAUGE_FORMAT, rates[ds_idx]);
    } else {
      WARNING("utils_format_kairosdb: invalid rates[ds_idx] for %s|%s|%s|%s|%s",
              vl->plugin, vl->plugin_instance, vl->type, vl->type_instance,
              ds->ds[ds_idx].name);
      sfree(rates);
      return -1;
    }
  } else if (ds->ds[ds_idx].type == DS_TYPE_COUNTER) {
    BUFFER_ADD("[[");
    BUFFER_ADD("%" PRIu64, CDTIME_T_TO_MS(vl->time));
    BUFFER_ADD(",");
    BUFFER_ADD("%llu", vl->values[ds_idx].counter);
  } else if (ds->ds[ds_idx].type == DS_TYPE_DERIVE) {
    BUFFER_ADD("[[");
    BUFFER_ADD("%" PRIu64, CDTIME_T_TO_MS(vl->time));
    BUFFER_ADD(",");
    BUFFER_ADD("%" PRIi64, vl->values[ds_idx].derive);
  } else if (ds->ds[ds_idx].type == DS_TYPE_ABSOLUTE) {
    BUFFER_ADD("[[");
    BUFFER_ADD("%" PRIu64, CDTIME_T_TO_MS(vl->time));
    BUFFER_ADD(",");
    BUFFER_ADD("%" PRIu64, vl->values[ds_idx].absolute);
  } else {
    ERROR("format_kairosdb: Unknown data source type: %i", ds->ds[ds_idx].type);
    sfree(rates);
    return -1;
  }
  BUFFER_ADD("]]");

#undef BUFFER_ADD

  DEBUG("format_kairosdb: values_to_kairosdb: buffer = %s;", buffer);
  sfree(rates);
  return 0;
}