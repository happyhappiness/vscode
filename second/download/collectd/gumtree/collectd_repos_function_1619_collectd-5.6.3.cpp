static int cx_handle_single_value_xpath(xmlXPathContextPtr xpath_ctx, /* {{{ */
                                        cx_xpath_t *xpath, const data_set_t *ds,
                                        value_list_t *vl, int index) {
  xmlXPathObjectPtr values_node_obj;
  xmlNodeSetPtr values_node;
  int tmp_size;
  char *node_value;

  values_node_obj =
      cx_evaluate_xpath(xpath_ctx, BAD_CAST xpath->values[index].path);
  if (values_node_obj == NULL)
    return (-1); /* Error already logged. */

  values_node = values_node_obj->nodesetval;
  tmp_size = (values_node) ? values_node->nodeNr : 0;

  if (tmp_size == 0) {
    WARNING("curl_xml plugin: "
            "relative xpath expression \"%s\" doesn't match any of the nodes. "
            "Skipping...",
            xpath->values[index].path);
    xmlXPathFreeObject(values_node_obj);
    return (-1);
  }

  if (tmp_size > 1) {
    WARNING("curl_xml plugin: "
            "relative xpath expression \"%s\" is expected to return "
            "only one node. Skipping...",
            xpath->values[index].path);
    xmlXPathFreeObject(values_node_obj);
    return (-1);
  }

  /* ignoring the element if other than textnode/attribute*/
  if (cx_if_not_text_node(values_node->nodeTab[0])) {
    WARNING("curl_xml plugin: "
            "relative xpath expression \"%s\" is expected to return "
            "only text/attribute node which is not the case. Skipping...",
            xpath->values[index].path);
    xmlXPathFreeObject(values_node_obj);
    return (-1);
  }

  node_value = (char *)xmlNodeGetContent(values_node->nodeTab[0]);
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

  /* free up object */
  xmlXPathFreeObject(values_node_obj);
  sfree(node_value);

  /* We have reached here which means that
   * we have got something to work */
  return (0);
}