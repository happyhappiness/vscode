static int ts_config_add_meta(meta_data_t **dest, /* {{{ */
                              const oconfig_item_t *ci, int may_be_empty) {
  char *key = NULL;
  char *string = NULL;
  int status;

  status = ts_util_get_key_and_string_wo_strdup(ci, &key, &string);
  if (status != 0)
    return (status);

  if (strlen(key) == 0) {
    ERROR("Target `set': The `%s' option does not accept empty string as "
          "first argument.",
          ci->key);
    return (-1);
  }

  if (!may_be_empty && (strlen(string) == 0)) {
    ERROR("Target `set': The `%s' option does not accept empty string as "
          "second argument.",
          ci->key);
    return (-1);
  }

  if ((*dest) == NULL) {
    /* Create a new meta_data_t */
    if ((*dest = meta_data_create()) == NULL) {
      ERROR("Target `set': failed to create a meta data for `%s'.", ci->key);
      return (-ENOMEM);
    }
  }

  return (meta_data_add_string(*dest, key, string));
}