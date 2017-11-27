static int sensor_list_remove_all(c_ipmi_instance_t *st) {
  c_ipmi_sensor_list_t *list_item;

  pthread_mutex_lock(&st->sensor_list_lock);

  list_item = st->sensor_list;
  st->sensor_list = NULL;

  pthread_mutex_unlock(&st->sensor_list_lock);

  while (list_item != NULL) {
    c_ipmi_sensor_list_t *list_next = list_item->next;

    free(list_item);

    list_item = list_next;
  } /* while (list_item) */

  return 0;
}