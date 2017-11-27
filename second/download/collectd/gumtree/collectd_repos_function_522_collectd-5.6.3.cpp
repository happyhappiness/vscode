static int ascent_xml_read_int(xmlDoc *doc, xmlNode *node, /* {{{ */
                               int *ret_value) {
  char *str_ptr;
  int value;

  str_ptr = (char *)xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
  if (str_ptr == NULL) {
    ERROR("ascent plugin: ascent_xml_read_int: xmlNodeListGetString failed.");
    return (-1);
  }

  if (strcasecmp("N/A", str_ptr) == 0)
    value = -1;
  else {
    char *end_ptr = NULL;
    value = strtol(str_ptr, &end_ptr, 0);
    if (str_ptr == end_ptr) {
      xmlFree(str_ptr);
      ERROR("ascent plugin: ascent_xml_read_int: strtol failed.");
      return (-1);
    }
  }
  xmlFree(str_ptr);

  *ret_value = value;
  return (0);
}