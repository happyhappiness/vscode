static int bind_xml_read_counter (xmlDoc *doc, xmlNode *node, /* {{{ */
    counter_t *ret_value)
{
  char *str_ptr, *end_ptr;
  long long int value;

  str_ptr = (char *) xmlNodeListGetString (doc, node->xmlChildrenNode, 1);
  if (str_ptr == NULL)
  {
    ERROR ("bind plugin: bind_xml_read_counter: xmlNodeListGetString failed.");
    return (-1);
  }

  errno = 0;
  value = strtoll (str_ptr, &end_ptr, 10);
  xmlFree(str_ptr);
  if (str_ptr == end_ptr || errno)
  {
    if (errno && (value < 0))
      ERROR ("bind plugin: bind_xml_read_counter: strtoll failed with underflow.");
    else if (errno && (value > 0))
      ERROR ("bind plugin: bind_xml_read_counter: strtoll failed with overflow.");
    else
      ERROR ("bind plugin: bind_xml_read_counter: strtoll failed.");
    return (-1);
  }

  *ret_value = value;
  return (0);
}