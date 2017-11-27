static int cx_handle_instance_xpath (xmlXPathContextPtr xpath_ctx, /* {{{ */
    cx_xpath_t *xpath, value_list_t *vl,
    _Bool is_table)
{
  xmlXPathObjectPtr instance_node_obj = NULL;
  xmlNodeSetPtr instance_node = NULL;

  memset (vl->type_instance, 0, sizeof (vl->type_instance));

  /* If the base xpath returns more than one block, the result is assumed to be
   * a table. The `Instnce' option is not optional in this case. Check for the
   * condition and inform the user. */
  if (is_table && (vl->type_instance == NULL))
  {
    WARNING ("curl_xml plugin: "
        "Base-XPath %s is a table (more than one result was returned), "
        "but no instance-XPath has been defined.",
        xpath->path);
    return (-1);
  }

  /* instance has to be an xpath expression */
  if (xpath->instance != NULL)
  {
    int tmp_size;

    instance_node_obj = cx_evaluate_xpath (xpath_ctx, BAD_CAST xpath->instance);
    if (instance_node_obj == NULL)
      return (-1); /* error is logged already */

    instance_node = instance_node_obj->nodesetval;
    tmp_size = (instance_node) ? instance_node->nodeNr : 0;

    if (tmp_size <= 0)
    {
      WARNING ("curl_xml plugin: "
          "relative xpath expression for 'InstanceFrom' \"%s\" doesn't match "
          "any of the nodes. Skipping the node.", xpath->instance);
      xmlXPathFreeObject (instance_node_obj);
      return (-1);
    }

    if (tmp_size > 1)
    {
      WARNING ("curl_xml plugin: "
          "relative xpath expression for 'InstanceFrom' \"%s\" is expected "
          "to return only one text node. Skipping the node.", xpath->instance);
      xmlXPathFreeObject (instance_node_obj);
      return (-1);
    }

    /* ignoring the element if other than textnode/attribute */
    if (cx_if_not_text_node(instance_node->nodeTab[0]))
    {
      WARNING ("curl_xml plugin: "
          "relative xpath expression \"%s\" is expected to return only text node "
          "which is not the case. Skipping the node.", xpath->instance);
      xmlXPathFreeObject (instance_node_obj);
      return (-1);
    }
  } /* if (xpath->instance != NULL) */

  if (xpath->instance_prefix != NULL)
  {
    if (instance_node != NULL)
      ssnprintf (vl->type_instance, sizeof (vl->type_instance),"%s%s",
          xpath->instance_prefix, (char *) xmlNodeGetContent(instance_node->nodeTab[0]));
    else
      sstrncpy (vl->type_instance, xpath->instance_prefix,
          sizeof (vl->type_instance));
  }
  else
  {
    /* If instance_prefix and instance_node are NULL, then
     * don't set the type_instance */
    if (instance_node != NULL)
      sstrncpy (vl->type_instance, (char *) xmlNodeGetContent(instance_node->nodeTab[0]),
          sizeof (vl->type_instance));
  }

  /* Free `instance_node_obj' this late, because `instance_node' points to
   * somewhere inside this structure. */
  xmlXPathFreeObject (instance_node_obj);

  return (0);
}