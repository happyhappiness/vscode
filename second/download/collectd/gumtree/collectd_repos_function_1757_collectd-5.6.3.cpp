int create_putval(char *ret, size_t ret_len, /* {{{ */
                  const data_set_t *ds, const value_list_t *vl) {
  char buffer_ident[6 * DATA_MAX_NAME_LEN];
  char buffer_values[1024];
  int status;

  status = FORMAT_VL(buffer_ident, sizeof(buffer_ident), vl);
  if (status != 0)
    return (status);
  escape_string(buffer_ident, sizeof(buffer_ident));

  status = format_values(buffer_values, sizeof(buffer_values), ds, vl,
                         /* store rates = */ 0);
  if (status != 0)
    return (status);
  escape_string(buffer_values, sizeof(buffer_values));

  ssnprintf(ret, ret_len, "PUTVAL %s interval=%.3f %s", buffer_ident,
            (vl->interval > 0) ? CDTIME_T_TO_DOUBLE(vl->interval)
                               : CDTIME_T_TO_DOUBLE(plugin_get_interval()),
            buffer_values);

  return (0);
}