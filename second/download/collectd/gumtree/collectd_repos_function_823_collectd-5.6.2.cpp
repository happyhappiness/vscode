static int bind_xml_read_derive(xmlDoc *doc, xmlNode *node, /* {{{ */
                                derive_t *ret_value) {
  char *str_ptr;
  value_t value;
  int status;

  str_ptr = (char *)xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
  if (str_ptr == NULL) {
    ERROR("bind plugin: bind_xml_read_derive: xmlNodeListGetString failed.");
    return (-1);
  }

  status = parse_value(str_ptr, &value, DS_TYPE_DERIVE);
  if (status != 0) {
    ERROR("bind plugin: Parsing string \"%s\" to derive value failed.",
          str_ptr);
    xmlFree(str_ptr);
    return (-1);
  }

  xmlFree(str_ptr);
  *ret_value = value.derive;
  return (0);
}