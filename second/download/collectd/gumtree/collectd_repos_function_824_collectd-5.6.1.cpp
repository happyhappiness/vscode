static int bind_xml_read_timestamp (const char *xpath_expression, /* {{{ */
    xmlDoc *doc, xmlXPathContext *xpathCtx, time_t *ret_value)
{
  xmlXPathObject *xpathObj = NULL;
  xmlNode *node;
  char *str_ptr;
  char *tmp;
  struct tm tm = { 0 };

  xpathObj = xmlXPathEvalExpression (BAD_CAST xpath_expression, xpathCtx);
  if (xpathObj == NULL)
  {
    ERROR ("bind plugin: Unable to evaluate XPath expression `%s'.",
        xpath_expression);
    return (-1);
  }

  if ((xpathObj->nodesetval == NULL) || (xpathObj->nodesetval->nodeNr < 1))
  {
    xmlXPathFreeObject (xpathObj);
    return (-1);
  }

  if (xpathObj->nodesetval->nodeNr != 1)
  {
    NOTICE ("bind plugin: Evaluating the XPath expression `%s' returned "
        "%i nodes. Only handling the first one.",
        xpath_expression, xpathObj->nodesetval->nodeNr);
  }

  node = xpathObj->nodesetval->nodeTab[0];

  if (node->xmlChildrenNode == NULL)
  {
    ERROR ("bind plugin: bind_xml_read_timestamp: "
        "node->xmlChildrenNode == NULL");
    xmlXPathFreeObject (xpathObj);
    return (-1);
  }

  str_ptr = (char *) xmlNodeListGetString (doc, node->xmlChildrenNode, 1);
  if (str_ptr == NULL)
  {
    ERROR ("bind plugin: bind_xml_read_timestamp: xmlNodeListGetString failed.");
    xmlXPathFreeObject (xpathObj);
    return (-1);
  }

  tmp = strptime (str_ptr, "%Y-%m-%dT%T", &tm);
  xmlFree(str_ptr);
  if (tmp == NULL)
  {
    ERROR ("bind plugin: bind_xml_read_timestamp: strptime failed.");
    xmlXPathFreeObject (xpathObj);
    return (-1);
  }

  *ret_value = mktime(&tm);

  xmlXPathFreeObject (xpathObj);
  return (0);
}