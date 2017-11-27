static void cc_submit(const web_page_t *wp, const web_match_t *wm, /* {{{ */
                      value_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  vl.values = &value;
  vl.values_len = 1;
  sstrncpy(vl.plugin, "curl", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, wp->instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, wm->type, sizeof(vl.type));
  if (wm->instance != NULL)
    sstrncpy(vl.type_instance, wm->instance, sizeof(vl.type_instance));

  plugin_dispatch_values(&vl);
}