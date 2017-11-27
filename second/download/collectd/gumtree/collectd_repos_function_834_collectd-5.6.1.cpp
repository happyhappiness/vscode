static int bind_xml_stats (int version, xmlDoc *doc, /* {{{ */
    xmlXPathContext *xpathCtx, xmlNode *statsnode)
{
  time_t current_time = 0;
  int status;

  xpathCtx->node = statsnode;

  /* TODO: Check `server/boot-time' to recognize server restarts. */

  status = bind_xml_read_timestamp ("server/current-time",
      doc, xpathCtx, &current_time);
  if (status != 0)
  {
    ERROR ("bind plugin: Reading `server/current-time' failed.");
    return (-1);
  }
  DEBUG ("bind plugin: Current server time is %i.", (int) current_time);

  if (version == 3)
  {
    bind_xml_stats_v3(doc, xpathCtx, statsnode, current_time);
  }
  else
  {
    bind_xml_stats_v1_v2(version, doc, xpathCtx, statsnode, current_time);
  }

  /* XPath:  memory/summary
   * Variables: TotalUse, InUse, BlockSize, ContextSize, Lost
   * Layout: v2 and v3:
   *   <summary>
   *     <TotalUse>6587096</TotalUse>
   *     <InUse>1345424</InUse>
   *     <BlockSize>5505024</BlockSize>
   *     <ContextSize>3732456</ContextSize>
   *     <Lost>0</Lost>
   *   </summary>
   */
  if (global_memory_stats != 0)
  {
    translation_table_ptr_t table_ptr =
    {
      memsummary_translation_table,
      memsummary_translation_table_length,
      /* plugin_instance = */ "global-memory_stats"
    };

    bind_parse_generic_value_list ("memory/summary",
          /* callback = */ bind_xml_table_callback,
          /* user_data = */ &table_ptr,
          doc, xpathCtx, current_time, DS_TYPE_GAUGE);
  }

  if (views_num > 0)
    bind_xml_stats_search_views (version, doc, xpathCtx, statsnode,
        current_time);

  return 0;
}