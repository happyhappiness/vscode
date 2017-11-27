static int mb_read_data(mb_host_t *host, mb_slave_t *slave, /* {{{ */
                        mb_data_t *data) {
  uint16_t values[2] = {0};
  int values_num;
  const data_set_t *ds;
  int status = 0;

  if ((host == NULL) || (slave == NULL) || (data == NULL))
    return (EINVAL);

  ds = plugin_get_ds(data->type);
  if (ds == NULL) {
    ERROR("Modbus plugin: Type \"%s\" is not defined.", data->type);
    return (-1);
  }

  if (ds->ds_num != 1) {
    ERROR("Modbus plugin: The type \"%s\" has %zu data sources. "
          "I can only handle data sets with only one data source.",
          data->type, ds->ds_num);
    return (-1);
  }

  if ((ds->ds[0].type != DS_TYPE_GAUGE) &&
      (data->register_type != REG_TYPE_INT32) &&
      (data->register_type != REG_TYPE_UINT32)) {
    NOTICE(
        "Modbus plugin: The data source of type \"%s\" is %s, not gauge. "
        "This will most likely result in problems, because the register type "
        "is not UINT32.",
        data->type, DS_TYPE_TO_STRING(ds->ds[0].type));
  }

  if ((data->register_type == REG_TYPE_INT32) ||
      (data->register_type == REG_TYPE_UINT32) ||
      (data->register_type == REG_TYPE_FLOAT))
    values_num = 2;
  else
    values_num = 1;

  if (host->connection == NULL) {
    status = EBADF;
  } else if (host->conntype == MBCONN_TCP) {
    /* getpeername() is used only to determine if the socket is connected, not
     * because we're really interested in the peer's IP address. */
    if (getpeername(modbus_get_socket(host->connection),
                    (void *)&(struct sockaddr_storage){0},
                    &(socklen_t){sizeof(struct sockaddr_storage)}) != 0)
      status = errno;