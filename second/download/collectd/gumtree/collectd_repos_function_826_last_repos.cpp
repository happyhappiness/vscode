static int bind_xml_read_gauge(xmlDoc *doc, xmlNode *node, /* {{{ */
                               gauge_t *ret_value) {
  char *str_ptr, *end_ptr;
  double value;

  str_ptr = (char *)xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
  if (str_ptr == NULL) {
    ERROR("bind plugin: bind_xml_read_gauge: xmlNodeListGetString failed.");
    return -1;
  }

  errno = 0;
  value = strtod(str_ptr, &end_ptr);
  xmlFree(str_ptr);
  if (str_ptr == end_ptr || errno) {
    if (errno && (value < 0))
      ERROR("bind plugin: bind_xml_read_gauge: strtod failed with underflow.");
    else if (errno && (value > 0))
      ERROR("bind plugin: bind_xml_read_gauge: strtod failed with overflow.");
    else
      ERROR("bind plugin: bind_xml_read_gauge: strtod failed.");
    return -1;
  }

  *ret_value = (gauge_t)value;
  return 0;
}