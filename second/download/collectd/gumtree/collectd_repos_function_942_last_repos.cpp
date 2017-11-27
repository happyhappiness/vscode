static int conn_handle_line(char *buffer) {
  char *fields[32];
  int fields_len;

  char *endptr;

  char *port_local_str;
  char *port_remote_str;
  uint16_t port_local;
  uint16_t port_remote;

  uint8_t state;

  int buffer_len = strlen(buffer);

  while ((buffer_len > 0) && (buffer[buffer_len - 1] < 32))
    buffer[--buffer_len] = '\0';
  if (buffer_len <= 0)
    return -1;

  fields_len = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
  if (fields_len < 12) {
    DEBUG("tcpconns plugin: Got %i fields, expected at least 12.", fields_len);
    return -1;
  }

  port_local_str = strchr(fields[1], ':');
  port_remote_str = strchr(fields[2], ':');

  if ((port_local_str == NULL) || (port_remote_str == NULL))
    return -1;
  port_local_str++;
  port_remote_str++;
  if ((*port_local_str == '\0') || (*port_remote_str == '\0'))
    return -1;

  endptr = NULL;
  port_local = (uint16_t)strtol(port_local_str, &endptr, 16);
  if ((endptr == NULL) || (*endptr != '\0'))
    return -1;

  endptr = NULL;
  port_remote = (uint16_t)strtol(port_remote_str, &endptr, 16);
  if ((endptr == NULL) || (*endptr != '\0'))
    return -1;

  endptr = NULL;
  state = (uint8_t)strtol(fields[3], &endptr, 16);
  if ((endptr == NULL) || (*endptr != '\0'))
    return -1;

  return conn_handle_ports(port_local, port_remote, state);
}