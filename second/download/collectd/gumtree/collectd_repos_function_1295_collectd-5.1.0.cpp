static int cx_parse_stats_xml(xmlChar* xml, cx_t *db) /* {{{ */
{
  int status;
  xmlDocPtr doc;
  xmlXPathContextPtr xpath_ctx;

  /* Load the XML */
  doc = xmlParseDoc(xml);
  if (doc == NULL)
  {
    ERROR ("curl_xml plugin: Failed to parse the xml document  - %s", xml);
    return (-1);
  }

  xpath_ctx = xmlXPathNewContext(doc);
  if(xpath_ctx == NULL)
  {
    ERROR ("curl_xml plugin: Failed to create the xml context");
    xmlFreeDoc(doc);
    return (-1);
  }

  status = cx_handle_parsed_xml (doc, xpath_ctx, db);
  /* Cleanup */
  xmlXPathFreeContext(xpath_ctx);
  xmlFreeDoc(doc);
  return status;
}