static staging_entry_t *staging_entry_get (const char *host, /* {{{ */
    const char *name,
    const char *type, const char *type_instance,
    int values_len)
{
  char key[2 * DATA_MAX_NAME_LEN];
  staging_entry_t *se;
  int status;

  if (staging_tree == NULL)
    return (NULL);

  ssnprintf (key, sizeof (key), "%s/%s/%s", host, type,
      (type_instance != NULL) ? type_instance : "");

  se = NULL;
  status = c_avl_get (staging_tree, key, (void *) &se);
  if (status == 0)
    return (se);

  /* insert new entry */
  se = (staging_entry_t *) malloc (sizeof (*se));
  if (se == NULL)
    return (NULL);
  memset (se, 0, sizeof (*se));

  sstrncpy (se->key, key, sizeof (se->key));
  se->flags = 0;

  se->vl.values = (value_t *) calloc (values_len, sizeof (*se->vl.values));
  if (se->vl.values == NULL)
  {
    sfree (se);
    return (NULL);
  }
  se->vl.values_len = values_len;

  se->vl.time = 0;
  se->vl.interval = 0;
  sstrncpy (se->vl.host, host, sizeof (se->vl.host));
  sstrncpy (se->vl.plugin, "gmond", sizeof (se->vl.plugin));
  sstrncpy (se->vl.type, type, sizeof (se->vl.type));
  if (type_instance != NULL)
    sstrncpy (se->vl.type_instance, type_instance,
        sizeof (se->vl.type_instance));

  status = c_avl_insert (staging_tree, se->key, se);
  if (status != 0)
  {
    ERROR ("gmond plugin: c_avl_insert failed.");
    sfree (se->vl.values);
    sfree (se);
    return (NULL);
  }

  return (se);
}