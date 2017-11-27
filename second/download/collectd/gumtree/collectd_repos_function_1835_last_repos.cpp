static int cx_handle_all_value_xpaths(xmlXPathContextPtr xpath_ctx, /* {{{ */
                                      cx_xpath_t *xpath, const data_set_t *ds,
                                      value_list_t *vl) {
  value_t values[xpath->values_len];

  assert(xpath->values_len > 0);
  assert(xpath->values_len == vl->values_len);
  assert(xpath->values_len == ds->ds_num);
  vl->values = values;

  for (size_t i = 0; i < xpath->values_len; i++) {
    if (cx_handle_single_value_xpath(xpath_ctx, xpath, ds, vl, i) != 0)
      return -1; /* An error has been printed. */
  }              /* for (i = 0; i < xpath->values_len; i++) */

  plugin_dispatch_values(vl);
  vl->values = NULL;

  return 0;
}