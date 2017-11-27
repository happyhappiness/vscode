static int ts_config_add_meta_delete(ts_key_list_t **dest, /* {{{ */
                                     const oconfig_item_t *ci) {
  ts_key_list_t *entry = NULL;

  entry = calloc(1, sizeof(*entry));
  if (entry == NULL) {
    ERROR("ts_config_add_meta_delete: calloc failed.");
    return (-ENOMEM);
  }

  if (cf_util_get_string(ci, &entry->key) != 0) {
    ts_key_list_free(entry);
    return (-1); /* An error has already been reported. */
  }

  if (strlen(entry->key) == 0) {
    ERROR("Target `set': The `%s' option does not accept empty string as "
          "first argument.",
          ci->key);
    ts_key_list_free(entry);
    return (-1);
  }

  entry->next = *dest;
  *dest = entry;

  return (0);
}