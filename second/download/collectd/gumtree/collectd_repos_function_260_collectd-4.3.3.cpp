static int uc_send_notification (const char *name)
{
  cache_entry_t *ce = NULL;
  int status;

  char *name_copy;
  char *host;
  char *plugin;
  char *plugin_instance;
  char *type;
  char *type_instance;

  notification_t n;

  name_copy = strdup (name);
  if (name_copy == NULL)
  {
    ERROR ("uc_send_notification: strdup failed.");
    return (-1);
  }

  status = parse_identifier (name_copy, &host,
      &plugin, &plugin_instance,
      &type, &type_instance);
  if (status != 0)
  {
    ERROR ("uc_send_notification: Cannot parse name `%s'", name);
    return (-1);
  }

  /* Copy the associative members */
  notification_init (&n, NOTIF_FAILURE, /* host = */ NULL,
      host, plugin, plugin_instance, type, type_instance);

  sfree (name_copy);
  name_copy = host = plugin = plugin_instance = type = type_instance = NULL;

  pthread_mutex_lock (&cache_lock);

  /*
   * Set the time _after_ getting the lock because we don't know how long
   * acquiring the lock takes and we will use this time later to decide
   * whether or not the state is OKAY.
   */
  n.time = time (NULL);

  status = c_avl_get (cache_tree, name, (void *) &ce);
  if (status != 0)
  {
    pthread_mutex_unlock (&cache_lock);
    sfree (name_copy);
    return (-1);
  }
    
  /* Check if the entry has been updated in the meantime */
  if ((n.time - ce->last_update) < (2 * ce->interval))
  {
    ce->state = STATE_OKAY;
    pthread_mutex_unlock (&cache_lock);
    sfree (name_copy);
    return (-1);
  }

  snprintf (n.message, sizeof (n.message),
      "%s has not been updated for %i seconds.", name,
      (int) (n.time - ce->last_update));

  pthread_mutex_unlock (&cache_lock);

  n.message[sizeof (n.message) - 1] = '\0';
  plugin_dispatch_notification (&n);

  return (0);
}