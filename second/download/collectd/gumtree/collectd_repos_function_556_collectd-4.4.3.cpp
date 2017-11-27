static int sensor_list_remove_all (void)
{
  c_ipmi_sensor_list_t *list_item;

  pthread_mutex_lock (&sensor_list_lock);

  list_item = sensor_list;
  sensor_list = NULL;

  pthread_mutex_unlock (&sensor_list_lock);

  while (list_item != NULL)
  {
    c_ipmi_sensor_list_t *list_next = list_item->next;

    free (list_item);

    list_item = list_next;
  } /* while (list_item) */

  return (0);
}