static const char *sensor_unit_to_type(ipmi_sensor_t *sensor) {
  static const c_ipmi_db_type_map_t ipmi_db_type_map[] = {
      {IPMI_UNIT_TYPE_WATTS, "power"}, {IPMI_UNIT_TYPE_CFM, "flow"}};

  /* check the modifier and rate of the sensor value */
  if ((ipmi_sensor_get_modifier_unit_use(sensor) != IPMI_MODIFIER_UNIT_NONE) ||
      (ipmi_sensor_get_rate_unit(sensor) != IPMI_RATE_UNIT_NONE))
    return NULL;

  /* find the db type by using sensor base unit type */
  enum ipmi_unit_type_e ipmi_type = ipmi_sensor_get_base_unit(sensor);
  for (int i = 0; i < STATIC_ARRAY_SIZE(ipmi_db_type_map); i++)
    if (ipmi_db_type_map[i].type == ipmi_type)
      return ipmi_db_type_map[i].type_name;

  return NULL;
}