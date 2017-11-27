static int ascent_xml_sessions_plr(xmlDoc *doc, xmlNode *node, /* {{{ */
                                   player_info_t *pi) {
  for (xmlNode *child = node->xmlChildrenNode; child != NULL;
       child = child->next) {
    if ((xmlStrcmp((const xmlChar *)"comment", child->name) == 0) ||
        (xmlStrcmp((const xmlChar *)"text", child->name) == 0))
      /* ignore */;
    else if (xmlStrcmp((const xmlChar *)"race", child->name) == 0)
      ascent_xml_read_int(doc, child, &pi->race);
    else if (xmlStrcmp((const xmlChar *)"class", child->name) == 0)
      ascent_xml_read_int(doc, child, &pi->class);
    else if (xmlStrcmp((const xmlChar *)"gender", child->name) == 0)
      ascent_xml_read_int(doc, child, &pi->gender);
    else if (xmlStrcmp((const xmlChar *)"level", child->name) == 0)
      ascent_xml_read_int(doc, child, &pi->level);
    else if (xmlStrcmp((const xmlChar *)"latency", child->name) == 0)
      ascent_xml_read_int(doc, child, &pi->latency);
    else if ((xmlStrcmp((const xmlChar *)"name", child->name) == 0) ||
             (xmlStrcmp((const xmlChar *)"pvprank", child->name) == 0) ||
             (xmlStrcmp((const xmlChar *)"map", child->name) == 0) ||
             (xmlStrcmp((const xmlChar *)"areaid", child->name) == 0) ||
             (xmlStrcmp((const xmlChar *)"xpos", child->name) == 0) ||
             (xmlStrcmp((const xmlChar *)"ypos", child->name) == 0) ||
             (xmlStrcmp((const xmlChar *)"onime", child->name) == 0))
      /* ignore */;
    else {
      WARNING("ascent plugin: ascent_xml_status: Unknown tag: %s", child->name);
    }
  } /* for (child) */

  return 0;
}