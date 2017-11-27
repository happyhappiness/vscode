static int sensor_list_remove (ipmi_sensor_t *sensor)
{
  ipmi_sensor_id_t sensor_id;
  c_ipmi_sensor_list_t *list_item;
  c_ipmi_sensor_list_t *list_prev;

  sensor_id = ipmi_sensor_convert_to_id (sensor);

  pthread_mutex_lock (&sensor_list_lock);

  list_prev = NULL;
  for (list_item = sensor_list;
      list_item != NULL;
      list_item = list_item->next)
  {
    if (ipmi_cmp_sensor_id (sensor_id, list_item->sensor_id) == 0)
      break;
    list_prev = list_item;
  } /* for (list_item) */

  if (list_item == NULL)
  {
    pthread_mutex_unlock (&sensor_list_lock);
    return (-1);
  }

  if (list_prev == NULL)
    sensor_list = list_item->next;
  else
    list_prev->next = list_item->next;

  list_prev = NULL;
  list_item->next = NULL;

  pthread_mutex_unlock (&sensor_list_lock);

  if (c_ipmi_nofiy_remove && c_ipmi_active)
  {
    notification_t n = { NOTIF_WARNING, cdtime (), "", "",
                         "ipmi", "", "", "", NULL };

    sstrncpy (n.host, hostname_g, sizeof (n.host));
    sstrncpy (n.type_instance, list_item->sensor_name,
              sizeof (n.type_instance));
    sstrncpy (n.type, list_item->sensor_type, sizeof (n.type));
    ssnprintf (n.message, sizeof (n.message),
              "sensor %s removed", list_item->sensor_name);

    plugin_dispatch_notification (&n);
  }

  free (list_item);
  return (0);
}