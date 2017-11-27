static int bind_parse_generic_name_attr_value_list(
    const char *xpath_expression, /* {{{ */
    list_callback_t list_callback, void *user_data, xmlDoc *doc,
    xmlXPathContext *xpathCtx, time_t current_time, int ds_type) {
  xmlXPathObject *xpathObj = NULL;
  int num_entries;

  xpathObj = xmlXPathEvalExpression(BAD_CAST xpath_expression, xpathCtx);
  if (xpathObj == NULL) {
    ERROR("bind plugin: Unable to evaluate XPath expression `%s'.",
          xpath_expression);
    return (-1);
  }

  num_entries = 0;
  /* Iterate over all matching nodes. */
  for (int i = 0; xpathObj->nodesetval && (i < xpathObj->nodesetval->nodeNr);
       i++) {
    /* Iterate over all child nodes. */
    for (xmlNode *child = xpathObj->nodesetval->nodeTab[i]->xmlChildrenNode;
         child != NULL; child = child->next) {
      if (child->type != XML_ELEMENT_NODE)
        continue;

      if (strncmp("counter", (char *)child->name, strlen("counter")) != 0)
        continue;

      char *attr_name;
      value_t value;
      int status;

      attr_name = (char *)xmlGetProp(child, BAD_CAST "name");
      if (attr_name == NULL) {
        DEBUG("bind plugin: found <counter> without name.");
        continue;
      }
      if (ds_type == DS_TYPE_GAUGE)
        status = bind_xml_read_gauge(doc, child, &value.gauge);
      else
        status = bind_xml_read_derive(doc, child, &value.derive);
      if (status != 0)
        continue;

      status = (*list_callback)(attr_name, value, current_time, user_data);
      if (status == 0)
        num_entries++;
    }
  }

  DEBUG("bind plugin: Found %d %s for XPath expression `%s'", num_entries,
        (num_entries == 1) ? "entry" : "entries", xpath_expression);

  xmlXPathFreeObject(xpathObj);

  return (0);
}