int format_values(char *ret, size_t ret_len, /* {{{ */
                  const data_set_t *ds, const value_list_t *vl,
                  _Bool store_rates) {
  size_t offset = 0;
  int status;
  gauge_t *rates = NULL;

  assert(0 == strcmp(ds->type, vl->type));

  memset(ret, 0, ret_len);

#define BUFFER_ADD(...)                                                        \
  do {                                                                         \
    status = ssnprintf(ret + offset, ret_len - offset, __VA_ARGS__);           \
    if (status < 1) {                                                          \
      sfree(rates);                                                            \
      return (-1);                                                             \
    } else if (((size_t)status) >= (ret_len - offset)) {                       \
      sfree(rates);                                                            \
      return (-1);                                                             \
    } else                                                                     \
      offset += ((size_t)status);                                              \
  } while (0)

  BUFFER_ADD("%.3f", CDTIME_T_TO_DOUBLE(vl->time));

  for (size_t i = 0; i < ds->ds_num; i++) {
    if (ds->ds[i].type == DS_TYPE_GAUGE)
      BUFFER_ADD(":" GAUGE_FORMAT, vl->values[i].gauge);
    else if (store_rates) {
      if (rates == NULL)
        rates = uc_get_rate(ds, vl);
      if (rates == NULL) {
        WARNING("format_values: uc_get_rate failed.");
        return (-1);
      }
      BUFFER_ADD(":" GAUGE_FORMAT, rates[i]);
    } else if (ds->ds[i].type == DS_TYPE_COUNTER)
      BUFFER_ADD(":%llu", vl->values[i].counter);
    else if (ds->ds[i].type == DS_TYPE_DERIVE)
      BUFFER_ADD(":%" PRIi64, vl->values[i].derive);
    else if (ds->ds[i].type == DS_TYPE_ABSOLUTE)
      BUFFER_ADD(":%" PRIu64, vl->values[i].absolute);
    else {
      ERROR("format_values: Unknown data source type: %i", ds->ds[i].type);
      sfree(rates);
      return (-1);
    }
  } /* for ds->ds_num */

#undef BUFFER_ADD

  sfree(rates);
  return (0);
}