static char *cx_get_text_node_value(xmlXPathContextPtr xpath_ctx, /* {{{ */
                                    char *expr, const char *from_option) {
  xmlXPathObjectPtr values_node_obj = cx_evaluate_xpath(xpath_ctx, expr);
  if (values_node_obj == NULL)
    return NULL; /* Error already logged. */

  xmlNodeSetPtr values_node = values_node_obj->nodesetval;
  size_t tmp_size = (values_node) ? values_node->nodeNr : 0;

  if (tmp_size == 0) {
    WARNING("curl_xml plugin: "
            "relative xpath expression \"%s\" from '%s' doesn't match "
            "any of the nodes.",
            expr, from_option);
    xmlXPathFreeObject(values_node_obj);
    return NULL;
  }

  if (tmp_size > 1) {
    WARNING("curl_xml plugin: "
            "relative xpath expression \"%s\" from '%s' is expected to return "
            "only one text node. Skipping the node.",
            expr, from_option);
    xmlXPathFreeObject(values_node_obj);
    return NULL;
  }

  /* ignoring the element if other than textnode/attribute*/
  if (cx_if_not_text_node(values_node->nodeTab[0])) {
    WARNING("curl_xml plugin: "
            "relative xpath expression \"%s\" from '%s' is expected to return "
            "only text/attribute node which is not the case. "
            "Skipping the node.",
            expr, from_option);
    xmlXPathFreeObject(values_node_obj);
    return NULL;
  }

  char *node_value = (char *)xmlNodeGetContent(values_node->nodeTab[0]);

  /* free up object */
  xmlXPathFreeObject(values_node_obj);

  return node_value;
}