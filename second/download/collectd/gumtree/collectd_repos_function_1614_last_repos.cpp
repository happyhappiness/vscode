static int values_to_json(char *buffer, size_t buffer_size, /* {{{ */
                          const data_set_t *ds, const value_list_t *vl,
                          int store_rates) {
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

  BUFFER_ADD("[");
  for (size_t i = 0; i < ds->ds_num; i++) {
    if (i > 0)
      BUFFER_ADD(",");

    if (ds->ds[i].type == DS_TYPE_GAUGE) {
      if (isfinite(vl->values[i].gauge))
        BUFFER_ADD(JSON_GAUGE_FORMAT, vl->values[i].gauge);
      else
        BUFFER_ADD("null");
    } else if (store_rates) {
      if (rates == NULL)
        rates = uc_get_rate(ds, vl);
      if (rates == NULL) {
        WARNING("utils_format_json: uc_get_rate failed.");
        sfree(rates);
        return -1;
      }

      if (isfinite(rates[i]))
        BUFFER_ADD(JSON_GAUGE_FORMAT, rates[i]);
      else
        BUFFER_ADD("null");
    } else if (ds->ds[i].type == DS_TYPE_COUNTER)
      BUFFER_ADD("%llu", vl->values[i].counter);
    else if (ds->ds[i].type == DS_TYPE_DERIVE)
      BUFFER_ADD("%" PRIi64, vl->values[i].derive);
    else if (ds->ds[i].type == DS_TYPE_ABSOLUTE)
      BUFFER_ADD("%" PRIu64, vl->values[i].absolute);
    else {
      ERROR("format_json: Unknown data source type: %i", ds->ds[i].type);
      sfree(rates);
      return -1;
    }
  } /* for ds->ds_num */
  BUFFER_ADD("]");

#undef BUFFER_ADD

  DEBUG("format_json: values_to_json: buffer = %s;", buffer);
  sfree(rates);
  return 0;
}