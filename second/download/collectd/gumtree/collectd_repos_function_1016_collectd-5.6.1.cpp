static void cc_submit_response_code (const web_page_t *wp, long code) /* {{{ */
{
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge = code;

  vl.values = values;
  vl.values_len = 1;
  sstrncpy (vl.host, hostname_g, sizeof (vl.host));
  sstrncpy (vl.plugin, "curl", sizeof (vl.plugin));
  sstrncpy (vl.plugin_instance, wp->instance, sizeof (vl.plugin_instance));
  sstrncpy (vl.type, "response_code", sizeof (vl.type));

  plugin_dispatch_values (&vl);
}