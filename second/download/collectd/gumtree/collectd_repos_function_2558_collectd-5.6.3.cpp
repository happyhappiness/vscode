int meta_data_add_signed_int(meta_data_t *md, /* {{{ */
                             const char *key, int64_t value) {
  meta_entry_t *e;

  if ((md == NULL) || (key == NULL))
    return (-EINVAL);

  e = md_entry_alloc(key);
  if (e == NULL)
    return (-ENOMEM);

  e->value.mv_signed_int = value;
  e->type = MD_TYPE_SIGNED_INT;

  return (md_entry_insert(md, e));
}