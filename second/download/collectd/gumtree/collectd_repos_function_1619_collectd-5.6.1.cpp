static int  cx_handle_base_xpath (char const *plugin_instance, /* {{{ */
    char const *host,
    xmlXPathContextPtr xpath_ctx, const data_set_t *ds,
    char *base_xpath, cx_xpath_t *xpath)
{
  int total_nodes;

  xmlXPathObjectPtr base_node_obj = NULL;
  xmlNodeSetPtr base_nodes = NULL;

  value_list_t vl = VALUE_LIST_INIT;

  base_node_obj = cx_evaluate_xpath (xpath_ctx, BAD_CAST base_xpath);
  if (base_node_obj == NULL)
    return -1; /* error is logged already */

  base_nodes = base_node_obj->nodesetval;
  total_nodes = (base_nodes) ? base_nodes->nodeNr : 0;

  if (total_nodes == 0)
  {
     ERROR ("curl_xml plugin: "
              "xpath expression \"%s\" doesn't match any of the nodes. "
              "Skipping the xpath block...", base_xpath);
     xmlXPathFreeObject (base_node_obj);
     return -1;
  }

  /* If base_xpath returned multiple results, then */
  /* Instance in the xpath block is required */
  if (total_nodes > 1 && xpath->instance == NULL)
  {
    ERROR ("curl_xml plugin: "
             "InstanceFrom is must in xpath block since the base xpath expression \"%s\" "
             "returned multiple results. Skipping the xpath block...", base_xpath);
    return -1;
  }

  /* set the values for the value_list */
  vl.values_len = ds->ds_num;
  sstrncpy (vl.type, xpath->type, sizeof (vl.type));
  sstrncpy (vl.plugin, "curl_xml", sizeof (vl.plugin));
  sstrncpy (vl.host, host, sizeof (vl.host));
  if (plugin_instance != NULL)
    sstrncpy (vl.plugin_instance, plugin_instance, sizeof (vl.plugin_instance));

  for (int i = 0; i < total_nodes; i++)
  {
    int status;

    xpath_ctx->node = base_nodes->nodeTab[i];

    status = cx_handle_instance_xpath (xpath_ctx, xpath, &vl,
        /* is_table = */ (total_nodes > 1));
    if (status != 0)
      continue; /* An error has already been reported. */

    status = cx_handle_all_value_xpaths (xpath_ctx, xpath, ds, &vl);
    if (status != 0)
      continue; /* An error has been logged. */
  } /* for (i = 0; i < total_nodes; i++) */

  /* free up the allocated memory */
  xmlXPathFreeObject (base_node_obj);

  return (0);
}