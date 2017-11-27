static int ascent_xml_sessions(xmlDoc *doc, xmlNode *node) /* {{{ */
{
  player_stats_t ps = {.level_sum = 0};

  for (xmlNode *child = node->xmlChildrenNode; child != NULL;
       child = child->next) {
    if ((xmlStrcmp((const xmlChar *)"comment", child->name) == 0) ||
        (xmlStrcmp((const xmlChar *)"text", child->name) == 0))
      /* ignore */;
    else if (xmlStrcmp((const xmlChar *)"plr", child->name) == 0) {
      int status;
      player_info_t pi = PLAYER_INFO_STATIC_INIT;

      status = ascent_xml_sessions_plr(doc, child, &pi);
      if (status == 0)
        ascent_account_player(&ps, &pi);
    } else {
      WARNING("ascent plugin: ascent_xml_status: Unknown tag: %s", child->name);
    }
  } /* for (child) */

  ascent_submit_players(&ps);

  return 0;
}