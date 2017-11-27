static int sensor_list_add(c_ipmi_instance_t *st, ipmi_sensor_t *sensor) {
  ipmi_sensor_id_t sensor_id;
  c_ipmi_sensor_list_t *list_item;
  c_ipmi_sensor_list_t *list_prev;

  char buffer[DATA_MAX_NAME_LEN] = {0};
  char *sensor_name_ptr = buffer;
  int sensor_type;
  const char *type;

  sensor_id = ipmi_sensor_convert_to_id(sensor);
  sensor_get_name(sensor, buffer, sizeof(buffer));

  DEBUG("ipmi plugin: sensor_list_add: Found sensor `%s` of `%s`,"
        " Type: %#x"
        " Event reading type: %#x"
        " Direction: %#x"
        " Event support: %#x",
        sensor_name_ptr, st->name, ipmi_sensor_get_sensor_type(sensor),
        ipmi_sensor_get_event_reading_type(sensor),
        ipmi_sensor_get_sensor_direction(sensor),
        ipmi_sensor_get_event_support(sensor));

  /* Both `ignorelist' and `sensor_name_ptr' may be NULL. */
  if (ignorelist_match(st->ignorelist, sensor_name_ptr) != 0)
    return 0;

  /* FIXME: Use rate unit or base unit to scale the value */

  sensor_type = ipmi_sensor_get_sensor_type(sensor);

  /*
   * ipmitool/lib/ipmi_sdr.c sdr_sensor_has_analog_reading() has a notice
   * about 'Threshold sensors' and 'analog readings'. Discrete sensor may
   * have analog data, but discrete sensors support is not implemented
   * in Collectd yet.
   *
   * ipmi_sensor_id_get_reading() supports only 'Threshold' sensors.
   * See lib/sensor.c:4842, stand_ipmi_sensor_get_reading() for details.
   */
  if (!ipmi_sensor_get_is_readable(sensor)) {
    INFO("ipmi plugin: sensor_list_add: Ignore sensor `%s` of `%s`, "
         "because it isn't readable! Its type: (%#x, %s). ",
         sensor_name_ptr, st->name, sensor_type,
         ipmi_sensor_get_sensor_type_string(sensor));
    return -1;
  }

  if (ipmi_sensor_get_event_reading_type(sensor) !=
      IPMI_EVENT_READING_TYPE_THRESHOLD) {
    INFO("ipmi plugin: sensor_list_add: Ignore sensor `%s` of `%s`, "
         "because it is discrete (%#x)! Its type: (%#x, %s). ",
         sensor_name_ptr, st->name, sensor_type,
         ipmi_sensor_get_event_reading_type(sensor),
         ipmi_sensor_get_sensor_type_string(sensor));
    return -1;
  }

  switch (sensor_type) {
  case IPMI_SENSOR_TYPE_TEMPERATURE:
    type = "temperature";
    break;

  case IPMI_SENSOR_TYPE_VOLTAGE:
    type = "voltage";
    break;

  case IPMI_SENSOR_TYPE_CURRENT:
    type = "current";
    break;

  case IPMI_SENSOR_TYPE_FAN:
    type = "fanspeed";
    break;

  case IPMI_SENSOR_TYPE_MEMORY:
    type = "memory";
    break;

  default: {
    /* try to get collectd DB type based on sensor base unit type */
    if ((type = sensor_unit_to_type(sensor)) != NULL)
      break;

    INFO("ipmi plugin: sensor_list_add: Ignore sensor `%s` of `%s`, "
         "because I don't know how to handle its units (%#x, %#x, %#x). "
         "Sensor type: (%#x, %s). If you need this sensor, please file "
         "a bug report at http://collectd.org/.",
         sensor_name_ptr, st->name, ipmi_sensor_get_base_unit(sensor),
         ipmi_sensor_get_modifier_unit(sensor),
         ipmi_sensor_get_rate_unit(sensor), sensor_type,
         ipmi_sensor_get_sensor_type_string(sensor));
    return -1;
  }
  } /* switch (sensor_type) */

  pthread_mutex_lock(&st->sensor_list_lock);

  list_prev = NULL;
  for (list_item = st->sensor_list; list_item != NULL;
       list_item = list_item->next) {
    if (ipmi_cmp_sensor_id(sensor_id, list_item->sensor_id) == 0)
      break;
    list_prev = list_item;
  } /* for (list_item) */

  if (list_item != NULL) {
    pthread_mutex_unlock(&st->sensor_list_lock);
    return 0;
  }

  list_item = (c_ipmi_sensor_list_t *)calloc(1, sizeof(c_ipmi_sensor_list_t));
  if (list_item == NULL) {
    pthread_mutex_unlock(&st->sensor_list_lock);
    return -1;
  }

  list_item->instance = st;
  list_item->sensor_id = ipmi_sensor_convert_to_id(sensor);

  if (list_prev != NULL)
    list_prev->next = list_item;
  else
    st->sensor_list = list_item;

  /* if sensor provides the percentage value, use "percent" collectd type
     and add the `percent` to the type instance of the reported value */
  if (ipmi_sensor_get_percentage(sensor)) {
    snprintf(list_item->type_instance, sizeof(list_item->type_instance),
             "percent-%s", sensor_name_ptr);
    type = "percent";
  } else {
    /* use type instance as a name of the sensor */
    sstrncpy(list_item->type_instance, sensor_name_ptr,
             sizeof(list_item->type_instance));
  }

  sstrncpy(list_item->sensor_name, sensor_name_ptr,
           sizeof(list_item->sensor_name));
  sstrncpy(list_item->sensor_type, type, sizeof(list_item->sensor_type));

  pthread_mutex_unlock(&st->sensor_list_lock);

  if (st->notify_add && (st->init_in_progress == 0)) {
    notification_t n = c_ipmi_notification_init(st, NOTIF_OKAY);

    sstrncpy(n.type_instance, list_item->type_instance,
             sizeof(n.type_instance));
    sstrncpy(n.type, list_item->sensor_type, sizeof(n.type));
    snprintf(n.message, sizeof(n.message), "sensor %s added",
             list_item->sensor_name);

    plugin_dispatch_notification(&n);
  }

  return 0;
}