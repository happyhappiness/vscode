int meta_data_get_string (meta_data_t *md, /* {{{ */
    const char *key, char **value)
{
  meta_entry_t *e;
  char *temp;

  if ((md == NULL) || (key == NULL) || (value == NULL))
    return (-EINVAL);

  pthread_mutex_lock (&md->lock);

  e = md_entry_lookup (md, key);
  if (e == NULL)
  {
    pthread_mutex_unlock (&md->lock);
    return (-ENOENT);
  }

  if (e->type != MD_TYPE_STRING)
  {
    ERROR ("meta_data_get_signed_int: Type mismatch for key `%s'", e->key);
    pthread_mutex_unlock (&md->lock);
    return (-ENOENT);
  }

  temp = md_strdup (e->value.mv_string);
  if (temp == NULL)
  {
    pthread_mutex_unlock (&md->lock);
    ERROR ("meta_data_get_string: md_strdup failed.");
    return (-ENOMEM);
  }
 
  pthread_mutex_unlock (&md->lock);

  *value = temp;

  return (0);
}