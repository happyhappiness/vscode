static void entity_sensor_update_handler (enum ipmi_update_e op,
    ipmi_entity_t *entity,
    ipmi_sensor_t *sensor,
    void *user_data)
{
  /* TODO: Ignore sensors we cannot read */

  if ((op == IPMI_ADDED) || (op == IPMI_CHANGED))
  {
    /* Will check for duplicate entries.. */
    sensor_list_add (sensor);
  }
  else if (op == IPMI_DELETED)
  {
    sensor_list_remove (sensor);
  }
}