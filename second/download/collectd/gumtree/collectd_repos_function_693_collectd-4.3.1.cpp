static int ut_threshold_add (const threshold_t *th)
{
  char name[6 * DATA_MAX_NAME_LEN];
  char *name_copy;
  threshold_t *th_copy;
  int status = 0;

  if (format_name (name, sizeof (name), th->host,
	th->plugin, th->plugin_instance,
	th->type, th->type_instance) != 0)
  {
    ERROR ("ut_threshold_add: format_name failed.");
    return (-1);
  }

  name_copy = strdup (name);
  if (name_copy == NULL)
  {
    ERROR ("ut_threshold_add: strdup failed.");
    return (-1);
  }

  th_copy = (threshold_t *) malloc (sizeof (threshold_t));
  if (th_copy == NULL)
  {
    sfree (name_copy);
    ERROR ("ut_threshold_add: malloc failed.");
    return (-1);
  }
  memcpy (th_copy, th, sizeof (threshold_t));

  DEBUG ("ut_threshold_add: Adding entry `%s'", name);

  pthread_mutex_lock (&threshold_lock);
  status = c_avl_insert (threshold_tree, name_copy, th_copy);
  pthread_mutex_unlock (&threshold_lock);

  if (status != 0)
  {
    ERROR ("ut_threshold_add: c_avl_insert (%s) failed.", name);
    sfree (name_copy);
    sfree (th_copy);
  }

  return (status);
}