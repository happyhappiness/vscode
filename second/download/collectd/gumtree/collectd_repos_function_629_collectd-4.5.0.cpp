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

  c_ipmi_sensor_list_t *list_item = (c_ipmi_sensor_list_t *)user_data;

  if (err != 0)
  {
    if ((err & 0xff) == IPMI_NOT_PRESENT_CC)
    {
      if (list_item->sensor_not_present == 0)
      {
        list_item->sensor_not_present = 1;

        INFO ("ipmi plugin: sensor_read_handler: sensor %s "
            "not present.", list_item->sensor_name);

        if (c_ipmi_nofiy_notpresent)
        {
          notification_t n = { NOTIF_WARNING, time(NULL), "", "", "ipmi",
            "", "", "", NULL };

          sstrncpy (n.host, hostname_g, sizeof (n.host));
          sstrncpy (n.type_instance, list_item->sensor_name,
              sizeof (n.type_instance));
          sstrncpy (n.type, list_item->sensor_type, sizeof (n.type));
          ssnprintf (n.message, sizeof (n.message),
              "sensor %s not present", list_item->sensor_name);

          plugin_dispatch_notification (&n);
        }
      }
    }
    else
    {
      INFO ("ipmi plugin: sensor_read_handler: Removing sensor %s, "
          "because it failed with status %#x.",
          list_item->sensor_name, err);
      sensor_list_remove (sensor);
    }
    return;
  }
  else if (list_item->sensor_not_present == 1)
  {
    list_item->sensor_not_present = 0;

    INFO ("ipmi plugin: sensor_read_handler: sensor %s present.",
        list_item->sensor_name);

    if (c_ipmi_nofiy_notpresent)
    {
      notification_t n = { NOTIF_OKAY, time(NULL), "", "", "ipmi",
        "", "", "", NULL };

      sstrncpy (n.host, hostname_g, sizeof (n.host));
      sstrncpy (n.type_instance, list_item->sensor_name,
          sizeof (n.type_instance));
      sstrncpy (n.type, list_item->sensor_type, sizeof (n.type));
      ssnprintf (n.message, sizeof (n.message),
          "sensor %s present", list_item->sensor_name);

      plugin_dispatch_notification (&n);
    }
  }

  if (value_present != IPMI_BOTH_VALUES_PRESENT)
  {
    INFO ("ipmi plugin: sensor_read_handler: Removing sensor %s, "
        "because it provides %s. If you need this sensor, "
        "please file a bug report.",
        list_item->sensor_name,
        (value_present == IPMI_RAW_VALUE_PRESENT)
        ? "only the raw value"
        : "no value");
    sensor_list_remove (sensor);
    return;
  }

  values[0].gauge = value;

  vl.values = values;
  vl.values_len = 1;
  vl.time = time (NULL);

  sstrncpy (vl.host, hostname_g, sizeof (vl.host));
  sstrncpy (vl.plugin, "ipmi", sizeof (vl.plugin));
  sstrncpy (vl.type, list_item->sensor_type, sizeof (vl.type));
  sstrncpy (vl.type_instance, list_item->sensor_name, sizeof (vl.type_instance));

  plugin_dispatch_values (&vl);
}