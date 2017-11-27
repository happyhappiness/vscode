static int bind_xml_stats_search_views(int version, xmlDoc *doc, /* {{{ */
                                       xmlXPathContext *xpathCtx,
                                       xmlNode *statsnode,
                                       time_t current_time) {
  xmlXPathObject *view_nodes = NULL;
  xmlXPathContext *view_path_context;

  view_path_context = xmlXPathNewContext(doc);
  if (view_path_context == NULL) {
    ERROR("bind plugin: xmlXPathNewContext failed.");
    return (-1);
  }

  view_nodes = xmlXPathEvalExpression(BAD_CAST "views/view", xpathCtx);
  if (view_nodes == NULL) {
    ERROR("bind plugin: Cannot find any <view> tags.");
    xmlXPathFreeContext(view_path_context);
    return (-1);
  }

  for (int i = 0; i < view_nodes->nodesetval->nodeNr; i++) {
    xmlNode *node;

    node = view_nodes->nodesetval->nodeTab[i];
    assert(node != NULL);

    view_path_context->node = node;

    bind_xml_stats_handle_view(version, doc, view_path_context, node,
                               current_time);
  }

  xmlXPathFreeObject(view_nodes);
  xmlXPathFreeContext(view_path_context);
  return (0);
}