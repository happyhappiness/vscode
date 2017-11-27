static int bind_parse_generic_name_value (const char *xpath_expression, /* {{{ */
    list_callback_t list_callback,
    void *user_data,
    xmlDoc *doc, xmlXPathContext *xpathCtx,
    time_t current_time, int ds_type)
{
  xmlXPathObject *xpathObj = NULL;
  int num_entries;
  int i;

  xpathObj = xmlXPathEvalExpression(BAD_CAST xpath_expression, xpathCtx);
  if (xpathObj == NULL)
  {
    ERROR("bind plugin: Unable to evaluate XPath expression `%s'.",
        xpath_expression);
    return (-1);
  }

  num_entries = 0;
  /* Iterate over all matching nodes. */
  for (i = 0; xpathObj->nodesetval && (i < xpathObj->nodesetval->nodeNr); i++)
  {
    xmlNode *name_node = NULL;
    xmlNode *counter = NULL;
    xmlNode *parent;
    xmlNode *child;

    parent = xpathObj->nodesetval->nodeTab[i];
    DEBUG ("bind plugin: bind_parse_generic_name_value: parent->name = %s;",
        (char *) parent->name);

    /* Iterate over all child nodes. */
    for (child = parent->xmlChildrenNode;
        child != NULL;
        child = child->next)
    {
      if (child->type != XML_ELEMENT_NODE)
        continue;

      if (xmlStrcmp (BAD_CAST "name", child->name) == 0)
        name_node = child;
      else if (xmlStrcmp (BAD_CAST "counter", child->name) == 0)
        counter = child;
    }

    if ((name_node != NULL) && (counter != NULL))
    {
      char *name = (char *) xmlNodeListGetString (doc,
          name_node->xmlChildrenNode, 1);
      value_t value;
      int status;

      if (ds_type == DS_TYPE_GAUGE)
        status = bind_xml_read_gauge (doc, counter, &value.gauge);
      else
        status = bind_xml_read_counter (doc, counter, &value.counter);
      if (status != 0)
        continue;

      status = (*list_callback) (name, value, current_time, user_data);
      if (status == 0)
        num_entries++;

      xmlFree (name);
    }
  }

  DEBUG ("bind plugin: Found %d %s for XPath expression `%s'",
      num_entries, (num_entries == 1) ? "entry" : "entries",
      xpath_expression);

  xmlXPathFreeObject(xpathObj);

  return (0);
}