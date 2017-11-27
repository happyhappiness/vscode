static int mr_config_add_meta_regex(llist_t **meta, /* {{{ */
                                    oconfig_item_t *ci) {
  char *meta_key;
  llentry_t *entry;
  mr_regex_t *re_head;
  int status;
  char buffer[1024];

  if ((ci->values_num != 2) || (ci->values[0].type != OCONFIG_TYPE_STRING) ||
      (ci->values[1].type != OCONFIG_TYPE_STRING)) {
    log_warn("`%s' needs exactly two string arguments.", ci->key);
    return (-1);
  }

  if (*meta == NULL) {
    *meta = llist_create();
    if (*meta == NULL) {
      log_err("mr_config_add_meta_regex: llist_create failed.");
      return (-1);
    }
  }

  meta_key = ci->values[0].value.string;
  entry = llist_search(*meta, meta_key);
  if (entry == NULL) {
    meta_key = strdup(meta_key);
    if (meta_key == NULL) {
      log_err("mr_config_add_meta_regex: strdup failed.");
      return (-1);
    }
    entry = llentry_create(meta_key, NULL);
    if (entry == NULL) {
      log_err("mr_config_add_meta_regex: llentry_create failed.");
      sfree(meta_key);
      return (-1);
    }
    /* meta_key and entry will now be freed by mr_free_match(). */
    llist_append(*meta, entry);
  }

  ssnprintf(buffer, sizeof(buffer), "%s `%s'", ci->key, meta_key);
  /* Can't pass &entry->value into mr_add_regex, so copy in/out. */
  re_head = entry->value;
  status = mr_add_regex(&re_head, ci->values[1].value.string, buffer);
  if (status == 0) {
    entry->value = re_head;
  }
  return status;
}