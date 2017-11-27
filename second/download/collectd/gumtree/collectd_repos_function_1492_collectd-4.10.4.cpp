int meta_data_add_boolean (meta_data_t *md, /* {{{ */
    const char *key, _Bool value)
{
  meta_entry_t *e;

  if ((md == NULL) || (key == NULL))
    return (-EINVAL);

  e = md_entry_alloc (key);
  if (e == NULL)
    return (-ENOMEM);

  e->value.mv_boolean = value;
  e->type = MD_TYPE_BOOLEAN;

  return (md_entry_insert (md, e));
}