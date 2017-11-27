static void sensor_read_handler (ipmi_sensor_t *sensor,
    int err,
    enum ipmi_value_present_e value_present,
    unsigned int raw_value,
    double value,
    ipmi_states_t *states,
    void *user_data)
{
  value_t values[1];
  value_list_t vl = VALUE_LIST_INIT;

  char sensor_name[IPMI_SENSOR_NAME_LEN];
  char *sensor_name_ptr;
  int sensor_type;
  const char *type;

  memset (sensor_name, 0, sizeof (sensor_name));
  ipmi_sensor_get_name (sensor, sensor_name, sizeof (sensor_name));
  sensor_name[sizeof (sensor_name) - 1] = 0;

  sensor_name_ptr = strstr (sensor_name, ").");
  if (sensor_name_ptr == NULL)
    sensor_name_ptr = sensor_name;
  else
    sensor_name_ptr += 2;

  if (err != 0)
  {
    INFO ("ipmi plugin: sensor_read_handler: Removing sensor %s, "
        "because it failed with status %#x.",
        sensor_name_ptr, err);
    sensor_list_remove (sensor);
    return;
  }

  if (value_present != IPMI_BOTH_VALUES_PRESENT)
  {
    INFO ("ipmi plugin: sensor_read_handler: Removing sensor %s, "
        "because it provides %s. If you need this sensor, "
        "please file a bug report.",
        sensor_name_ptr,
        (value_present == IPMI_RAW_VALUE_PRESENT)
        ? "only the raw value"
        : "no value");
    sensor_list_remove (sensor);
    return;
  }

  /* Both `ignorelist' and `plugin_instance' may be NULL. */
  if (ignorelist_match (ignorelist, sensor_name_ptr) != 0)
  {
    sensor_list_remove (sensor);
    return;
  }

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
        INFO ("ipmi plugin: sensor_read_handler: Removing sensor %s, "
            "because I don't know how to handle its type (%#x, %s). "
            "If you need this sensor, please file a bug report.",
            sensor_name_ptr, sensor_type, sensor_type_str);
        sensor_list_remove (sensor);
        return;
      }
  } /* switch (sensor_type) */

  values[0].gauge = value;

  vl.values = values;
  vl.values_len = 1;
  vl.time = time (NULL);

  sstrncpy (vl.host, hostname_g, sizeof (vl.host));
  sstrncpy (vl.plugin, "ipmi", sizeof (vl.plugin));
  sstrncpy (vl.type_instance, sensor_name_ptr, sizeof (vl.type_instance));

  plugin_dispatch_values (type, &vl);
}