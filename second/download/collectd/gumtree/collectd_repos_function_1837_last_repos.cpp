static int cx_handle_xpath(const cx_t *db, /* {{{ */
                           xmlXPathContextPtr xpath_ctx, cx_xpath_t *xpath) {

  const data_set_t *ds = plugin_get_ds(xpath->type);
  if (cx_check_type(ds, xpath) != 0)
    return -1;

  xmlXPathObjectPtr base_node_obj = cx_evaluate_xpath(xpath_ctx, xpath->path);
  if (base_node_obj == NULL)
    return -1; /* error is logged already */

  xmlNodeSetPtr base_nodes = base_node_obj->nodesetval;
  int total_nodes = (base_nodes) ? base_nodes->nodeNr : 0;

  if (total_nodes == 0) {
    ERROR("curl_xml plugin: "
          "xpath expression \"%s\" doesn't match any of the nodes. "
          "Skipping the xpath block...",
          xpath->path);
    xmlXPathFreeObject(base_node_obj);
    return -1;
  }

  /* If base_xpath returned multiple results, then */
  /* InstanceFrom or PluginInstanceFrom in the xpath block is required */
  if (total_nodes > 1 && xpath->instance == NULL &&
      xpath->plugin_instance_from == NULL) {
    ERROR("curl_xml plugin: "
          "InstanceFrom or PluginInstanceFrom is must in xpath block "
          "since the base xpath expression \"%s\" "
          "returned multiple results. Skipping the xpath block...",
          xpath->path);
    xmlXPathFreeObject(base_node_obj);
    return -1;
  }

  value_list_t vl = VALUE_LIST_INIT;

  /* set the values for the value_list */
  vl.values_len = ds->ds_num;
  sstrncpy(vl.type, xpath->type, sizeof(vl.type));
  sstrncpy(vl.plugin, (db->plugin_name != NULL) ? db->plugin_name : "curl_xml",
           sizeof(vl.plugin));
  sstrncpy(vl.host, cx_host(db), sizeof(vl.host));

  for (int i = 0; i < total_nodes; i++) {
    xpath_ctx->node = base_nodes->nodeTab[i];

    if (db->instance != NULL)
      sstrncpy(vl.plugin_instance, db->instance, sizeof(vl.plugin_instance));

    if (cx_handle_instance_xpath(xpath_ctx, xpath, &vl) != 0)
      continue; /* An error has already been reported. */

    if (cx_handle_all_value_xpaths(xpath_ctx, xpath, ds, &vl) != 0)
      continue; /* An error has been logged. */
  }             /* for (i = 0; i < total_nodes; i++) */

  /* free up the allocated memory */
  xmlXPathFreeObject(base_node_obj);

  return 0;
}