static int cx_parse_xml(cx_t *db, char *xml) /* {{{ */
{
  /* Load the XML */
  xmlDocPtr doc = xmlParseDoc(BAD_CAST xml);
  if (doc == NULL) {
    ERROR("curl_xml plugin: Failed to parse the xml document  - %s", xml);
    return -1;
  }

  xmlXPathContextPtr xpath_ctx = xmlXPathNewContext(doc);
  if (xpath_ctx == NULL) {
    ERROR("curl_xml plugin: Failed to create the xml context");
    xmlFreeDoc(doc);
    return -1;
  }

  for (size_t i = 0; i < db->namespaces_num; i++) {
    cx_namespace_t const *ns = db->namespaces + i;
    int status =
        xmlXPathRegisterNs(xpath_ctx, BAD_CAST ns->prefix, BAD_CAST ns->url);
    if (status != 0) {
      ERROR("curl_xml plugin: "
            "unable to register NS with prefix=\"%s\" and href=\"%s\"\n",
            ns->prefix, ns->url);
      xmlXPathFreeContext(xpath_ctx);
      xmlFreeDoc(doc);
      return status;
    }
  }

  int status = cx_handle_parsed_xml(db, doc, xpath_ctx);
  /* Cleanup */
  xmlXPathFreeContext(xpath_ctx);
  xmlFreeDoc(doc);
  return status;
}