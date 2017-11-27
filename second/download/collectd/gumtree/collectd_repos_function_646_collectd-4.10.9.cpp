static int bind_xml_stats_handle_zone (int version, xmlDoc *doc, /* {{{ */
    xmlXPathContext *path_ctx, xmlNode *node, cb_view_t *view,
    time_t current_time)
{
  xmlXPathObject *path_obj;
  char *zone_name = NULL;
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
    zone_name = (char *) xmlNodeListGetString (doc,
        path_obj->nodesetval->nodeTab[i]->xmlChildrenNode, 1);
    if (zone_name != NULL)
      break;
  }

  if (zone_name == NULL)
  {
    ERROR ("bind plugin: Could not determine zone name.");
    xmlXPathFreeObject (path_obj);
    return (-1);
  }

  for (j = 0; j < view->zones_num; j++)
  {
    if (strcasecmp (zone_name, view->zones[j]) == 0)
      break;
  }

  xmlFree (zone_name);
  zone_name = NULL;

  if (j >= views_num)
  {
    xmlXPathFreeObject (path_obj);
    return (0);
  }

  zone_name = view->zones[j];

  DEBUG ("bind plugin: bind_xml_stats_handle_zone: Found zone `%s'.",
      zone_name);

  { /* Parse the <counters> tag {{{ */
    char plugin_instance[DATA_MAX_NAME_LEN];
    translation_table_ptr_t table_ptr =
    { 
      nsstats_translation_table,
      nsstats_translation_table_length,
      plugin_instance
    };

    ssnprintf (plugin_instance, sizeof (plugin_instance), "%s-zone-%s",
        view->name, zone_name);

    bind_parse_generic_value_list (/* xpath = */ "counters",
        /* callback = */ bind_xml_table_callback,
        /* user_data = */ &table_ptr,
        doc, path_ctx, current_time, DS_TYPE_COUNTER);
  } /* }}} */

  xmlXPathFreeObject (path_obj);

  return (0);
}