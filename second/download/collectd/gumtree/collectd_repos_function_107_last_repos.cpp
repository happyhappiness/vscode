static int lv_instance_include_domain(struct lv_read_instance *inst,
                                      const char *dom_name,
                                      const char *dom_tag) {
  if ((dom_tag[0] != '\0') && (strcmp(dom_tag, inst->tag) == 0))
    return 1;

  /* instance#0 will always be there, so it is in charge of extra duties */
  if (inst->id == 0) {
    if (dom_tag[0] == '\0' || !is_known_tag(dom_tag)) {
      DEBUG(PLUGIN_NAME " plugin#%s: refreshing domain %s "
                        "with unknown tag '%s'",
            inst->tag, dom_name, dom_tag);
      return 1;
    }
  }

  return 0;
}