static int cx_handle_instance_xpath(xmlXPathContextPtr xpath_ctx, /* {{{ */
                                    cx_xpath_t *xpath, value_list_t *vl) {

  /* Handle type instance */
  if (xpath->instance != NULL) {
    char *node_value =
        cx_get_text_node_value(xpath_ctx, xpath->instance, "InstanceFrom");
    if (node_value == NULL)
      return -1;

    if (xpath->instance_prefix != NULL)
      snprintf(vl->type_instance, sizeof(vl->type_instance), "%s%s",
               xpath->instance_prefix, node_value);
    else
      sstrncpy(vl->type_instance, node_value, sizeof(vl->type_instance));

    xmlFree(node_value);
  } else if (xpath->instance_prefix != NULL)
    sstrncpy(vl->type_instance, xpath->instance_prefix,
             sizeof(vl->type_instance));

  /* Handle plugin instance */
  if (xpath->plugin_instance_from != NULL) {
    char *node_value = cx_get_text_node_value(
        xpath_ctx, xpath->plugin_instance_from, "PluginInstanceFrom");

    if (node_value == NULL)
      return -1;

    sstrncpy(vl->plugin_instance, node_value, sizeof(vl->plugin_instance));
    xmlFree(node_value);
  }

  return 0;
}