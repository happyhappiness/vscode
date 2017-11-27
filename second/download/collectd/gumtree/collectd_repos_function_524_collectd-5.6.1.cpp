static int ascent_xml_status (xmlDoc *doc, xmlNode *node) /* {{{ */
{
  for (xmlNode *child = node->xmlChildrenNode; child != NULL; child = child->next)
  {
    if ((xmlStrcmp ((const xmlChar *) "comment", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "text", child->name) == 0))
      /* ignore */;
    else if (xmlStrcmp ((const xmlChar *) "alliance", child->name) == 0)
      ascent_xml_submit_gauge (doc, child, NULL, "players", "alliance");
    else if (xmlStrcmp ((const xmlChar *) "horde", child->name) == 0)
      ascent_xml_submit_gauge (doc, child, NULL, "players", "horde");
    else if (xmlStrcmp ((const xmlChar *) "qplayers", child->name) == 0)
      ascent_xml_submit_gauge (doc, child, NULL, "players", "queued");
    else if ((xmlStrcmp ((const xmlChar *) "acceptedconns", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "avglat", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "cdbquerysize", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "cpu", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "fthreads", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "gmcount", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "lastupdate", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "ontime", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "oplayers", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "peakcount", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "platform", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "ram", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "threads", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "uptime", child->name) == 0)
        || (xmlStrcmp ((const xmlChar *) "wdbquerysize", child->name) == 0))
      /* ignore */;
    else
    {
      WARNING ("ascent plugin: ascent_xml_status: Unknown tag: %s", child->name);
    }
  } /* for (child) */

  return (0);
}