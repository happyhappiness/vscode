static int bind_xml (const char *data) /* {{{ */
{
  xmlDoc *doc = NULL;
  xmlXPathContext *xpathCtx = NULL;
  xmlXPathObject *xpathObj = NULL;
  int ret = -1;
  int i;

  doc = xmlParseMemory (data, strlen (data));
  if (doc == NULL)
  {
    ERROR ("bind plugin: xmlParseMemory failed.");
    return (-1);
  }

  xpathCtx = xmlXPathNewContext (doc);
  if (xpathCtx == NULL)
  {
    ERROR ("bind plugin: xmlXPathNewContext failed.");
    xmlFreeDoc (doc);
    return (-1);
  }

  xpathObj = xmlXPathEvalExpression (BAD_CAST "/isc/bind/statistics", xpathCtx);
  if (xpathObj == NULL)
  {
    ERROR ("bind plugin: Cannot find the <statistics> tag.");
    xmlXPathFreeContext (xpathCtx);
    xmlFreeDoc (doc);
    return (-1);
  }
  else if (xpathObj->nodesetval == NULL)
  {
    ERROR ("bind plugin: xmlXPathEvalExpression failed.");
    xmlXPathFreeObject (xpathObj);
    xmlXPathFreeContext (xpathCtx);
    xmlFreeDoc (doc);
    return (-1);
  }

  for (i = 0; i < xpathObj->nodesetval->nodeNr; i++)
  {
    xmlNode *node;
    char *attr_version;
    int parsed_version = 0;

    node = xpathObj->nodesetval->nodeTab[i];
    assert (node != NULL);

    attr_version = (char *) xmlGetProp (node, BAD_CAST "version");
    if (attr_version == NULL)
    {
      NOTICE ("bind plugin: Found <statistics> tag doesn't have a "
          "`version' attribute.");
      continue;
    }
    DEBUG ("bind plugin: Found: <statistics version=\"%s\">", attr_version);

    /* At the time this plugin was written, version "1.0" was used by
     * BIND 9.5.0, version "2.0" was used by BIND 9.5.1 and 9.6.0. We assume
     * that "1.*" and "2.*" don't introduce structural changes, so we just
     * check for the first two characters here. */
    if (strncmp ("1.", attr_version, strlen ("1.")) == 0)
      parsed_version = 1;
    else if (strncmp ("2.", attr_version, strlen ("2.")) == 0)
      parsed_version = 2;
    else
    {
      /* TODO: Use the complaint mechanism here. */
      NOTICE ("bind plugin: Found <statistics> tag with version `%s'. "
          "Unfortunately I have no clue how to parse that. "
          "Please open a bug report for this.", attr_version);
      xmlFree (attr_version);
      continue;
    }

    ret = bind_xml_stats (parsed_version,
        doc, xpathCtx, node);

    xmlFree (attr_version);
    /* One <statistics> node ought to be enough. */
    break;
  }

  xmlXPathFreeObject (xpathObj);
  xmlXPathFreeContext (xpathCtx);
  xmlFreeDoc (doc);

  return (ret);
}