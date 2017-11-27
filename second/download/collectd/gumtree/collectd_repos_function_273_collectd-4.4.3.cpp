static int ascent_xml_submit_gauge (xmlDoc *doc, xmlNode *node, /* {{{ */
    const char *plugin_instance, const char *type, const char *type_instance)
{
  char *str_ptr;
  gauge_t value;

  str_ptr = (char *) xmlNodeListGetString (doc, node->xmlChildrenNode, 1);
  if (str_ptr == NULL)
  {
    ERROR ("ascent plugin: ascent_xml_submit_gauge: xmlNodeListGetString failed.");
    return (-1);
  }

  if (strcasecmp ("N/A", str_ptr) == 0)
    value = NAN;
  else
  {
    char *end_ptr = NULL;
    value = strtod (str_ptr, &end_ptr);
    if (str_ptr == end_ptr)
    {
      ERROR ("ascent plugin: ascent_xml_submit_gauge: strtod failed.");
      return (-1);
    }
  }

  return (ascent_submit_gauge (plugin_instance, type, type_instance, value));
}