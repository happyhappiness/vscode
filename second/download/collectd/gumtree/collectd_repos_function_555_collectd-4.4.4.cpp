static int sensor_list_read_all (void)
{
  c_ipmi_sensor_list_t *list_item;

  pthread_mutex_lock (&sensor_list_lock);

  for (list_item = sensor_list;
      list_item != NULL;
      list_item = list_item->next)
  {
    ipmi_sensor_id_get_reading (list_item->sensor_id,
        sensor_read_handler, /* user data = */ NULL);
  } /* for (list_item) */

  pthread_mutex_unlock (&sensor_list_lock);

  return (0);
}