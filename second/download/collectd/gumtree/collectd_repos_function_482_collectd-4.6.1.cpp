static int bind_xml_stats_handle_view (int version, xmlDoc *doc, /* {{{ */
    xmlXPathContext *path_ctx, xmlNode *node, time_t current_time)
{
  xmlXPathObject *path_obj;
  char *view_name = NULL;
  cb_view_t *view;
  int i;
  size_t j;

  path_obj = xmlXPathEvalExpression (BAD_CAST "name", path_ctx);
  if (path_obj == NULL)
  {
    ERROR ("bind plugin: xmlXPathEvalExpression failed.");
    return (-1);
  }

  for (i = 0; path_obj->nodesetval && (i < path_obj->nodesetval->nodeNr); i++)
  {
    view_name = (char *) xmlNodeListGetString (doc,
        path_obj->nodesetval->nodeTab[i]->xmlChildrenNode, 1);
    if (view_name != NULL)
      break;
  }

  if (view_name == NULL)
  {
    ERROR ("bind plugin: Could not determine view name.");
    xmlXPathFreeObject (path_obj);
    return (-1);
  }

  for (j = 0; j < views_num; j++)
  {
    if (strcasecmp (view_name, views[j].name) == 0)
      break;
  }

  xmlFree (view_name);
  xmlXPathFreeObject (path_obj);

  view_name = NULL;
  path_obj = NULL;

  if (j >= views_num)
    return (0);

  view = views + j;

  DEBUG ("bind plugin: bind_xml_stats_handle_view: Found view `%s'.",
      view->name);

  if (view->qtypes != 0) /* {{{ */
  {
    char plugin_instance[DATA_MAX_NAME_LEN];
    list_info_ptr_t list_info =
    {
      plugin_instance,
      /* type = */ "dns_qtype"
    };

    ssnprintf (plugin_instance, sizeof (plugin_instance), "%s-qtypes",
        view->name);

    bind_parse_generic_name_value (/* xpath = */ "rdtype",
        /* callback = */ bind_xml_list_callback,
        /* user_data = */ &list_info,
        doc, path_ctx, current_time);
  } /* }}} */

  if (view->resolver_stats != 0) /* {{{ */
  {
    char plugin_instance[DATA_MAX_NAME_LEN];
    translation_table_ptr_t table_ptr =
    { 
      resstats_translation_table,
      resstats_translation_table_length,
      plugin_instance
    };

    ssnprintf (plugin_instance, sizeof (plugin_instance),
        "%s-resolver_stats", view->name);

    bind_parse_generic_name_value ("resstat",
        /* callback = */ bind_xml_table_callback,
        /* user_data = */ &table_ptr,
        doc, path_ctx, current_time);
  } /* }}} */

  if (view->cacherrsets != 0) /* {{{ */
  {
    char plugin_instance[DATA_MAX_NAME_LEN];
    list_info_ptr_t list_info =
    {
      plugin_instance,
      /* type = */ "dns_qtype"
    };

    ssnprintf (plugin_instance, sizeof (plugin_instance), "%s-cache_rr_sets",
        view->name);

    bind_parse_generic_name_value (/* xpath = */ "cache/rrset",
        /* callback = */ bind_xml_list_callback,
        /* user_data = */ &list_info,
        doc, path_ctx, current_time);
  } /* }}} */

  if (view->zones_num > 0)
    bind_xml_stats_search_zones (version, doc, path_ctx, node, view,
        current_time);

  return (0);
}