static int sensor_list_add (ipmi_sensor_t *sensor)
{
  ipmi_sensor_id_t sensor_id;
  c_ipmi_sensor_list_t *list_item;
  c_ipmi_sensor_list_t *list_prev;

  char buffer[DATA_MAX_NAME_LEN];
  const char *entity_id_string;
  char sensor_name[DATA_MAX_NAME_LEN];
  char *sensor_name_ptr;
  int sensor_type;
  const char *type;
  ipmi_entity_t *ent = ipmi_sensor_get_entity(sensor);

  sensor_id = ipmi_sensor_convert_to_id (sensor);

  memset (buffer, 0, sizeof (buffer));
  ipmi_sensor_get_name (sensor, buffer, sizeof (buffer));
  buffer[sizeof (buffer) - 1] = 0;

  entity_id_string = ipmi_entity_get_entity_id_string (ent);

  if (entity_id_string == NULL)
    sstrncpy (sensor_name, buffer, sizeof (sensor_name));
  else
    ssnprintf (sensor_name, sizeof (sensor_name),
        "%s %s", buffer, entity_id_string);

  sstrncpy (buffer, sensor_name, sizeof (buffer));
  sensor_name_ptr = strstr (buffer, ").");
  if (sensor_name_ptr != NULL)
  {
    /* If name is something like "foo (123).bar",
     * change that to "bar (123)".
     * Both, sensor_name_ptr and sensor_id_ptr point to memory within the
     * `buffer' array, which holds a copy of the current `sensor_name'. */
    char *sensor_id_ptr;

    /* `sensor_name_ptr' points to ").bar". */
    sensor_name_ptr[1] = 0;
    /* `buffer' holds "foo (123)\0bar\0". */
    sensor_name_ptr += 2;
    /* `sensor_name_ptr' now points to "bar". */

    sensor_id_ptr = strstr (buffer, "(");
    if (sensor_id_ptr != NULL)
    {
      /* `sensor_id_ptr' now points to "(123)". */
      ssnprintf (sensor_name, sizeof (sensor_name),
          "%s %s", sensor_name_ptr, sensor_id_ptr); 
    }
    /* else: don't touch sensor_name. */
  }
  sensor_name_ptr = sensor_name;

  /* Both `ignorelist' and `plugin_instance' may be NULL. */
  if (ignorelist_match (ignorelist, sensor_name_ptr) != 0)
    return (0);

  /* FIXME: Use rate unit or base unit to scale the value */

  sensor_type = ipmi_sensor_get_sensor_type (sensor);
  switch (sensor_type)
  {
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

    default:
      {
        const char *sensor_type_str;

        sensor_type_str = ipmi_sensor_get_sensor_type_string (sensor);
        INFO ("ipmi plugin: sensor_list_add: Ignore sensor %s, "
            "because I don't know how to handle its type (%#x, %s). "
            "If you need this sensor, please file a bug report.",
            sensor_name_ptr, sensor_type, sensor_type_str);
        return (-1);
      }
  } /* switch (sensor_type) */

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

  if (list_item != NULL)
  {
    pthread_mutex_unlock (&sensor_list_lock);
    return (0);
  }

  list_item = (c_ipmi_sensor_list_t *) calloc (1, sizeof (c_ipmi_sensor_list_t));
  if (list_item == NULL)
  {
    pthread_mutex_unlock (&sensor_list_lock);
    return (-1);
  }

  list_item->sensor_id = ipmi_sensor_convert_to_id (sensor);

  if (list_prev != NULL)
    list_prev->next = list_item;
  else
    sensor_list = list_item;

  sstrncpy (list_item->sensor_name, sensor_name_ptr,
            sizeof (list_item->sensor_name));
  sstrncpy (list_item->sensor_type, type, sizeof (list_item->sensor_type));

  pthread_mutex_unlock (&sensor_list_lock);

  if (c_ipmi_nofiy_add && (c_ipmi_init_in_progress == 0))
  {
    notification_t n = { NOTIF_OKAY, time(NULL), "", "", "ipmi",
                         "", "", "", NULL };

    sstrncpy (n.host, hostname_g, sizeof (n.host));
    sstrncpy (n.type_instance, list_item->sensor_name,
              sizeof (n.type_instance));
    sstrncpy (n.type, list_item->sensor_type, sizeof (n.type));
    ssnprintf (n.message, sizeof (n.message),
              "sensor %s added", list_item->sensor_name);

    plugin_dispatch_notification (&n);
  }

  return (0);
}