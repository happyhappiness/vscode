static int bind_xml_stats_search_zones(int version, xmlDoc *doc, /* {{{ */
                                       xmlXPathContext *path_ctx, xmlNode *node,
                                       cb_view_t *view, time_t current_time) {
  xmlXPathObject *zone_nodes = NULL;
  xmlXPathContext *zone_path_context;

  zone_path_context = xmlXPathNewContext(doc);
  if (zone_path_context == NULL) {
    ERROR("bind plugin: xmlXPathNewContext failed.");
    return (-1);
  }

  zone_nodes = xmlXPathEvalExpression(BAD_CAST "zones/zone", path_ctx);
  if (zone_nodes == NULL) {
    ERROR("bind plugin: Cannot find any <view> tags.");
    xmlXPathFreeContext(zone_path_context);
    return (-1);
  }

  for (int i = 0; i < zone_nodes->nodesetval->nodeNr; i++) {
    node = zone_nodes->nodesetval->nodeTab[i];
    assert(node != NULL);

    zone_path_context->node = node;

    bind_xml_stats_handle_zone(version, doc, zone_path_context, node, view,
                               current_time);
  }

  xmlXPathFreeObject(zone_nodes);
  xmlXPathFreeContext(zone_path_context);
  return (0);
}