static void cmc_submit(const web_page_t *wp, const web_match_t *wm, /* {{{ */
                       const cu_match_value_t *mv) {
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  values[0] = mv->value;

  vl.values = values;
  vl.values_len = 1;
  sstrncpy(vl.host, hostname_g, sizeof(vl.host));
  sstrncpy(vl.plugin, "memcachec", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, wp->instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, wm->type, sizeof(vl.type));
  sstrncpy(vl.type_instance, wm->instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}