static void cmc_submit(const web_page_t *wp, const web_match_t *wm, /* {{{ */
                       value_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &value;
  vl.values_len = 1;
  sstrncpy(vl.plugin, (wp->plugin_name != NULL) ? wp->plugin_name : "memcachec",
           sizeof (vl.plugin));
  sstrncpy(vl.plugin_instance, wp->instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, wm->type, sizeof(vl.type));
  sstrncpy(vl.type_instance, wm->instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}