static int nut_read(user_data_t *user_data) {
  nut_ups_t *ups = user_data->data;
  const char *query[3] = {"VAR", ups->upsname, NULL};
  unsigned int query_num = 2;
  char **answer;
  unsigned int answer_num;
  int status;

  /* (Re-)Connect if we have no connection */
  if (ups->conn == NULL) {
    ups->conn = malloc(sizeof(*ups->conn));
    if (ups->conn == NULL) {
      ERROR("nut plugin: malloc failed.");
      return -1;
    }

    status = nut_connect(ups);
    if (status == -1)
      return -1;

  } /* if (ups->conn == NULL) */

  /* nut plugin: nut_read_one: upscli_list_start (adpos) failed: Protocol
   * error */
  status = upscli_list_start(ups->conn, query_num, query);
  if (status != 0) {
    ERROR("nut plugin: nut_read: upscli_list_start (%s) failed: %s",
          ups->upsname, upscli_strerror(ups->conn));
    upscli_disconnect(ups->conn);
    sfree(ups->conn);
    return -1;
  }

  while ((status = upscli_list_next(ups->conn, query_num, query, &answer_num,
                                    &answer)) == 1) {
    char *key;
    double value;

    if (answer_num < 4)
      continue;

    key = answer[2];
    value = atof(answer[3]);

    if (strncmp("ambient.", key, 8) == 0) {
      if (strcmp("ambient.humidity", key) == 0)
        nut_submit(ups, "humidity", "ambient", value);
      else if (strcmp("ambient.temperature", key) == 0)
        nut_submit(ups, "temperature", "ambient", value);
    } else if (strncmp("battery.", key, 8) == 0) {
      if (strcmp("battery.charge", key) == 0)
        nut_submit(ups, "percent", "charge", value);
      else if (strcmp("battery.current", key) == 0)
        nut_submit(ups, "current", "battery", value);
      else if (strcmp("battery.runtime", key) == 0)
        nut_submit(ups, "timeleft", "battery", value);
      else if (strcmp("battery.temperature", key) == 0)
        nut_submit(ups, "temperature", "battery", value);
      else if (strcmp("battery.voltage", key) == 0)
        nut_submit(ups, "voltage", "battery", value);
    } else if (strncmp("input.", key, 6) == 0) {
      if (strcmp("input.frequency", key) == 0)
        nut_submit(ups, "frequency", "input", value);
      else if (strcmp("input.voltage", key) == 0)
        nut_submit(ups, "voltage", "input", value);
    } else if (strncmp("output.", key, 7) == 0) {
      if (strcmp("output.current", key) == 0)
        nut_submit(ups, "current", "output", value);
      else if (strcmp("output.frequency", key) == 0)
        nut_submit(ups, "frequency", "output", value);
      else if (strcmp("output.voltage", key) == 0)
        nut_submit(ups, "voltage", "output", value);
    } else if (strncmp("ups.", key, 4) == 0) {
      if (strcmp("ups.load", key) == 0)
        nut_submit(ups, "percent", "load", value);
      else if (strcmp("ups.power", key) == 0)
        nut_submit(ups, "power", "ups", value);
      else if (strcmp("ups.temperature", key) == 0)
        nut_submit(ups, "temperature", "ups", value);
    }
  } /* while (upscli_list_next) */

  return 0;
}