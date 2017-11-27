static int cx_handle_single_value_xpath(xmlXPathContextPtr xpath_ctx, /* {{{ */
                                        cx_xpath_t *xpath, const data_set_t *ds,
                                        value_list_t *vl, int index) {

  char *node_value = cx_get_text_node_value(
      xpath_ctx, xpath->values[index].path, "ValuesFrom");

  if (node_value == NULL)
    return -1;

  switch (ds->ds[index].type) {
  case DS_TYPE_COUNTER:
    vl->values[index].counter =
        (counter_t)strtoull(node_value,
                            /* endptr = */ NULL, /* base = */ 0);
    break;
  case DS_TYPE_DERIVE:
    vl->values[index].derive =
        (derive_t)strtoll(node_value,
                          /* endptr = */ NULL, /* base = */ 0);
    break;
  case DS_TYPE_ABSOLUTE:
    vl->values[index].absolute =
        (absolute_t)strtoull(node_value,
                             /* endptr = */ NULL, /* base = */ 0);
    break;
  case DS_TYPE_GAUGE:
    vl->values[index].gauge = (gauge_t)strtod(node_value,
                                              /* endptr = */ NULL);
  }

  xmlFree(node_value);

  /* We have reached here which means that
   * we have got something to work */
  return 0;
}