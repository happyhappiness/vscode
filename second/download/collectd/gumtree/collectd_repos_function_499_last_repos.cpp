static int ascent_xml(const char *data) /* {{{ */
{
  xmlDoc *doc;
  xmlNode *cur;

#if 0
  doc = xmlParseMemory (data, strlen (data),
      /* URL = */ "ascent.xml",
      /* encoding = */ NULL,
      /* options = */ 0);
#else
  doc = xmlParseMemory(data, strlen(data));
#endif
  if (doc == NULL) {
    ERROR("ascent plugin: xmlParseMemory failed.");
    return -1;
  }

  cur = xmlDocGetRootElement(doc);
  if (cur == NULL) {
    ERROR("ascent plugin: XML document is empty.");
    xmlFreeDoc(doc);
    return -1;
  }

  if (xmlStrcmp((const xmlChar *)"serverpage", cur->name) != 0) {
    ERROR("ascent plugin: XML root element is not \"serverpage\".");
    xmlFreeDoc(doc);
    return -1;
  }

  for (xmlNode *child = cur->xmlChildrenNode; child != NULL;
       child = child->next) {
    if ((xmlStrcmp((const xmlChar *)"comment", child->name) == 0) ||
        (xmlStrcmp((const xmlChar *)"text", child->name) == 0))
      /* ignore */;
    else if (xmlStrcmp((const xmlChar *)"status", child->name) == 0)
      ascent_xml_status(doc, child);
    else if (xmlStrcmp((const xmlChar *)"instances", child->name) == 0)
      /* ignore for now */;
    else if (xmlStrcmp((const xmlChar *)"gms", child->name) == 0)
      /* ignore for now */;
    else if (xmlStrcmp((const xmlChar *)"sessions", child->name) == 0)
      ascent_xml_sessions(doc, child);
    else {
      WARNING("ascent plugin: ascent_xml: Unknown tag: %s", child->name);
    }
  } /* for (child) */

  xmlFreeDoc(doc);
  return 0;
}