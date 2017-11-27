static void cc_submit_response_time(const web_page_t *wp, /* {{{ */
                                    cdtime_t response_time) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0].gauge = CDTIME_T_TO_DOUBLE(response_time);

  vl.values = values;
  vl.values_len = 1;
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "curl", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, wp->instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, "response_time", sizeof(vl.type));

  plugin_dispatch_values(&vl);
}