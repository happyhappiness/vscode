static int cx_check_type(const data_set_t *ds, cx_xpath_t *xpath) /* {{{ */
{
  if (!ds) {
    WARNING("curl_xml plugin: DataSet `%s' not defined.", xpath->type);
    return -1;
  }

  if (ds->ds_num != xpath->values_len) {
    WARNING("curl_xml plugin: DataSet `%s' requires %zu values, but config "
            "talks about %zu",
            xpath->type, ds->ds_num, xpath->values_len);
    return -1;
  }

  return 0;
}