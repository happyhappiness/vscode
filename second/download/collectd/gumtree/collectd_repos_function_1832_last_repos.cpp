static int cx_if_not_text_node(xmlNodePtr node) /* {{{ */
{
  if (node->type == XML_TEXT_NODE || node->type == XML_ATTRIBUTE_NODE ||
      node->type == XML_ELEMENT_NODE)
    return 0;

  WARNING("curl_xml plugin: "
          "Node \"%s\" doesn't seem to be a text node. Skipping...",
          node->name);
  return -1;
}