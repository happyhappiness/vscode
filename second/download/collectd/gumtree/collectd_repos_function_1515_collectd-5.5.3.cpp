static int cx_parse_stats_xml(xmlChar* xml, cx_t *db) /* {{{ */
{
  int status;
  xmlDocPtr doc;
  xmlXPathContextPtr xpath_ctx;
  size_t i;

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

  for (i = 0; i < db->namespaces_num; i++)
  {
    cx_namespace_t const *ns = db->namespaces + i;
    status = xmlXPathRegisterNs (xpath_ctx,
        BAD_CAST ns->prefix, BAD_CAST ns->url);
    if (status != 0)
    {
      ERROR ("curl_xml plugin: "
          "unable to register NS with prefix=\"%s\" and href=\"%s\"\n",
          ns->prefix, ns->url);
      xmlXPathFreeContext(xpath_ctx);
      xmlFreeDoc (doc);
      return (status);
    }
  }

  status = cx_handle_parsed_xml (doc, xpath_ctx, db);
  /* Cleanup */
  xmlXPathFreeContext(xpath_ctx);
  xmlFreeDoc(doc);
  return status;
}