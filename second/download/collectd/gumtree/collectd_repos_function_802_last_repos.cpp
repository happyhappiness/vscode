static int format_kairosdb_value_list_nocheck(
    char *buffer, /* {{{ */
    size_t *ret_buffer_fill, size_t *ret_buffer_free, const data_set_t *ds,
    const value_list_t *vl, int store_rates, size_t temp_size,
    char const *const *http_attrs, size_t http_attrs_num, int data_ttl,
    char const *metrics_prefix) {
  char temp[temp_size];
  int status;

  status = value_list_to_kairosdb(temp, sizeof(temp), ds, vl, store_rates,
                                  http_attrs, http_attrs_num, data_ttl,
                                  metrics_prefix);
  if (status != 0)
    return status;
  temp_size = strlen(temp);

  memcpy(buffer + (*ret_buffer_fill), temp, temp_size + 1);
  (*ret_buffer_fill) += temp_size;
  (*ret_buffer_free) -= temp_size;

  return 0;
}