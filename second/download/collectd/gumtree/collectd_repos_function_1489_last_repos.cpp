static void sensor_get_name(ipmi_sensor_t *sensor, char *buffer, int buf_len) {
  char temp[DATA_MAX_NAME_LEN] = {0};
  ipmi_entity_t *ent = ipmi_sensor_get_entity(sensor);
  const char *entity_id_string = ipmi_entity_get_entity_id_string(ent);
  char sensor_name[DATA_MAX_NAME_LEN] = "";
  char *sensor_name_ptr;

  if ((buffer == NULL) || (buf_len == 0))
    return;

  ipmi_sensor_get_name(sensor, temp, sizeof(temp));
  temp[sizeof(temp) - 1] = 0;

  if (entity_id_string != NULL && strlen(temp))
    snprintf(sensor_name, sizeof(sensor_name), "%s %s", temp, entity_id_string);
  else if (entity_id_string != NULL)
    sstrncpy(sensor_name, entity_id_string, sizeof(sensor_name));
  else
    sstrncpy(sensor_name, temp, sizeof(sensor_name));

  if (strlen(temp)) {
    sstrncpy(temp, sensor_name, sizeof(temp));
    sensor_name_ptr = strstr(temp, ").");
    if (sensor_name_ptr != NULL) {
      /* If name is something like "foo (123).bar",
       * change that to "bar (123)".
       * Both, sensor_name_ptr and sensor_id_ptr point to memory within the
       * `temp' array, which holds a copy of the current `sensor_name'. */
      char *sensor_id_ptr;

      /* `sensor_name_ptr' points to ").bar". */
      sensor_name_ptr[1] = 0;
      /* `temp' holds "foo (123)\0bar\0". */
      sensor_name_ptr += 2;
      /* `sensor_name_ptr' now points to "bar". */

      sensor_id_ptr = strstr(temp, "(");
      if (sensor_id_ptr != NULL) {
        /* `sensor_id_ptr' now points to "(123)". */
        snprintf(sensor_name, sizeof(sensor_name), "%s %s", sensor_name_ptr,
                 sensor_id_ptr);
      }
      /* else: don't touch sensor_name. */
    }
  }
  sstrncpy(buffer, sensor_name, buf_len);
}