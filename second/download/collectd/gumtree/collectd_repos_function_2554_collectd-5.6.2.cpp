int meta_data_add_string(meta_data_t *md, /* {{{ */
                         const char *key, const char *value) {
  meta_entry_t *e;

  if ((md == NULL) || (key == NULL) || (value == NULL))
    return (-EINVAL);

  e = md_entry_alloc(key);
  if (e == NULL)
    return (-ENOMEM);

  e->value.mv_string = md_strdup(value);
  if (e->value.mv_string == NULL) {
    ERROR("meta_data_add_string: md_strdup failed.");
    md_entry_free(e);
    return (-ENOMEM);
  }
  e->type = MD_TYPE_STRING;

  return (md_entry_insert(md, e));
}