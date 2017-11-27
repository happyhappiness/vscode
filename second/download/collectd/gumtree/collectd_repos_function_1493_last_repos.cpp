static int sensor_list_read_all(c_ipmi_instance_t *st) {
  pthread_mutex_lock(&st->sensor_list_lock);

  for (c_ipmi_sensor_list_t *list_item = st->sensor_list; list_item != NULL;
       list_item = list_item->next) {
    DEBUG("ipmi plugin: try read sensor `%s` of `%s`, use: %d",
          list_item->sensor_name, st->name, list_item->use);

    /* Reading already initiated */
    if (list_item->use)
      continue;

    list_item->use++;
    ipmi_sensor_id_get_reading(list_item->sensor_id, sensor_read_handler,
                               /* user data = */ (void *)list_item);
  } /* for (list_item) */

  pthread_mutex_unlock(&st->sensor_list_lock);

  return 0;
}