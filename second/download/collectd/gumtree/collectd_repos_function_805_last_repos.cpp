int format_kairosdb_value_list(char *buffer, /* {{{ */
                               size_t *ret_buffer_fill, size_t *ret_buffer_free,
                               const data_set_t *ds, const value_list_t *vl,
                               int store_rates, char const *const *http_attrs,
                               size_t http_attrs_num, int data_ttl,
                               char const *metrics_prefix) {
  if ((buffer == NULL) || (ret_buffer_fill == NULL) ||
      (ret_buffer_free == NULL) || (ds == NULL) || (vl == NULL))
    return -EINVAL;

  if (*ret_buffer_free < 3)
    return -ENOMEM;

  return format_kairosdb_value_list_nocheck(
      buffer, ret_buffer_fill, ret_buffer_free, ds, vl, store_rates,
      (*ret_buffer_free) - 2, http_attrs, http_attrs_num, data_ttl,
      metrics_prefix);
}