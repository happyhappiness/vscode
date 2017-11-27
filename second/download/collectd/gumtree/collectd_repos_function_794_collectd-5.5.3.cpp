static int bind_xml_stats_handle_zone (int version, xmlDoc *doc, /* {{{ */
    xmlXPathContext *path_ctx, xmlNode *node, cb_view_t *view,
    time_t current_time)
{
  xmlXPathObject *path_obj;
  char *zone_name = NULL;
  int i;
  size_t j;

  if (version >= 3)
  {
    char *n = (char *) xmlGetProp (node, BAD_CAST "name");
    char *c = (char *) xmlGetProp (node, BAD_CAST "rdataclass");
    if (n && c)
    {
      zone_name = (char *) xmlMalloc(strlen(n) + strlen(c) + 2);
      snprintf(zone_name, strlen(n) + strlen(c) + 2, "%s/%s", n, c);
    }
    xmlFree(n);
    xmlFree(c);
  }
  else
  {
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
    xmlXPathFreeObject (path_obj);
  }

  if (zone_name == NULL)
  {
    ERROR ("bind plugin: Could not determine zone name.");
    return (-1);
  }

  for (j = 0; j < view->zones_num; j++)
  {
    if (strcasecmp (zone_name, view->zones[j]) == 0)
      break;
  }

  xmlFree (zone_name);
  zone_name = NULL;

  if (j >= view->zones_num)
    return (0);

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

    if (version == 3)
    {
      list_info_ptr_t list_info =
      {
        plugin_instance,
        /* type = */ "dns_qtype"
      };
      bind_parse_generic_name_attr_value_list (/* xpath = */ "counters[@type='rcode']",
        /* callback = */ bind_xml_table_callback,
        /* user_data = */ &table_ptr,
        doc, path_ctx, current_time, DS_TYPE_COUNTER);
      bind_parse_generic_name_attr_value_list (/* xpath = */ "counters[@type='qtype']",
        /* callback = */ bind_xml_list_callback,
        /* user_data = */ &list_info,
        doc, path_ctx, current_time, DS_TYPE_COUNTER);
    }
    else
    {
      bind_parse_generic_value_list (/* xpath = */ "counters",
          /* callback = */ bind_xml_table_callback,
          /* user_data = */ &table_ptr,
          doc, path_ctx, current_time, DS_TYPE_COUNTER);
    }
  } /* }}} */

  return (0);
}