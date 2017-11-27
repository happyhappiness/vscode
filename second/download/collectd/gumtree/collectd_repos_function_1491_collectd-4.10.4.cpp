int meta_data_add_double (meta_data_t *md, /* {{{ */
    const char *key, double value)
{
  meta_entry_t *e;

  if ((md == NULL) || (key == NULL))
    return (-EINVAL);

  e = md_entry_alloc (key);
  if (e == NULL)
    return (-ENOMEM);

  e->value.mv_double = value;
  e->type = MD_TYPE_DOUBLE;

  return (md_entry_insert (md, e));
}