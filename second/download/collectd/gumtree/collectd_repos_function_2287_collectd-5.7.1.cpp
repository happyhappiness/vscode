static void ts_subst(char *dest, size_t size, const char *string, /* {{{ */
                     const value_list_t *vl) {
  char temp[DATA_MAX_NAME_LEN];

  /* Initialize the field with the template. */
  sstrncpy(dest, string, size);

  if (strchr(dest, '%') == NULL)
    return;

#define REPLACE_FIELD(t, v)                                                    \
  if (subst_string(temp, sizeof(temp), dest, t, v) != NULL)                    \
    sstrncpy(dest, temp, size);
  REPLACE_FIELD("%{host}", vl->host);
  REPLACE_FIELD("%{plugin}", vl->plugin);
  REPLACE_FIELD("%{plugin_instance}", vl->plugin_instance);
  REPLACE_FIELD("%{type}", vl->type);
  REPLACE_FIELD("%{type_instance}", vl->type_instance);

  if (vl->meta != NULL) {
    char **meta_toc = NULL;
    int meta_entries = meta_data_toc(vl->meta, &meta_toc);
    if (meta_entries <= 0)
      return;

    for (int i = 0; i < meta_entries; i++) {
      char meta_name[DATA_MAX_NAME_LEN];
      char *value_str;
      const char *key = meta_toc[i];

      ssnprintf(meta_name, sizeof(meta_name), "%%{meta:%s}", key);
      if (meta_data_as_string(vl->meta, key, &value_str) != 0)
        continue;

      REPLACE_FIELD(meta_name, value_str);
      sfree(value_str);
    }

    strarray_free(meta_toc, (size_t)meta_entries);
  }
}