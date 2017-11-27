static int format_alert(yajl_gen g, notification_t const *n) /* {{{ */
{
  yajl_gen_array_open(g);
  yajl_gen_map_open(g); /* BEGIN alert */

  /*
   * labels
   */
  JSON_ADD(g, "labels");
  yajl_gen_map_open(g); /* BEGIN labels */

  JSON_ADD(g, "alertname");
  if (strncmp(n->plugin, n->type, strlen(n->plugin)) == 0)
    JSON_ADDF(g, "collectd_%s", n->type);
  else
    JSON_ADDF(g, "collectd_%s_%s", n->plugin, n->type);

  JSON_ADD(g, "instance");
  JSON_ADD(g, n->host);

  /* mangling of plugin instance and type instance into labels is copied from
   * the Prometheus collectd exporter. */
  if (strlen(n->plugin_instance) > 0) {
    JSON_ADD(g, n->plugin);
    JSON_ADD(g, n->plugin_instance);
  }
  if (strlen(n->type_instance) > 0) {
    if (strlen(n->plugin_instance) > 0)
      JSON_ADD(g, "type");
    else
      JSON_ADD(g, n->plugin);
    JSON_ADD(g, n->type_instance);
  }

  JSON_ADD(g, "severity");
  JSON_ADD(g,
           (n->severity == NOTIF_FAILURE)
               ? "FAILURE"
               : (n->severity == NOTIF_WARNING)
                     ? "WARNING"
                     : (n->severity == NOTIF_OKAY) ? "OKAY" : "UNKNOWN");

  JSON_ADD(g, "service");
  JSON_ADD(g, "collectd");

  yajl_gen_map_close(g); /* END labels */

  /*
   * annotations
   */
  JSON_ADD(g, "annotations");
  yajl_gen_map_open(g); /* BEGIN annotations */

  JSON_ADD(g, "summary");
  JSON_ADD(g, n->message);

  if (format_json_meta(g, n->meta) != 0)
    return -1;

  yajl_gen_map_close(g); /* END annotations */

  JSON_ADD(g, "startsAt");
  format_time(g, n->time);

  yajl_gen_map_close(g); /* END alert */
  yajl_gen_array_close(g);

  return 0;
}