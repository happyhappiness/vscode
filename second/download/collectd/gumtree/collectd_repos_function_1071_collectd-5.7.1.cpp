static void cc_submit_response_code(const web_page_t *wp, long code) /* {{{ */
{
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &(value_t){.gauge = (gauge_t)code};
  vl.values_len = 1;
  sstrncpy(vl.plugin, "curl", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, wp->instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "response_code", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}