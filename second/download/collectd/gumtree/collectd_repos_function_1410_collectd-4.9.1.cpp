int meta_data_get_signed_int (meta_data_t *md, /* {{{ */
    const char *key, int64_t *value)
{
  meta_entry_t *e;

  if ((md == NULL) || (key == NULL) || (value == NULL))
    return (-EINVAL);

  pthread_mutex_lock (&md->lock);

  e = md_entry_lookup (md, key);
  if (e == NULL)
  {
    pthread_mutex_unlock (&md->lock);
    return (-ENOENT);
  }

  if (e->type != MD_TYPE_SIGNED_INT)
  {
    ERROR ("meta_data_get_signed_int: Type mismatch for key `%s'", e->key);
    pthread_mutex_unlock (&md->lock);
    return (-ENOENT);
  }

  *value = e->value.mv_signed_int;

  pthread_mutex_unlock (&md->lock);
  return (0);
}