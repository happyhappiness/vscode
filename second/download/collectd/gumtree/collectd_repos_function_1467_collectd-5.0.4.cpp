static int mb_read_data (mb_host_t *host, mb_slave_t *slave, /* {{{ */
    mb_data_t *data)
{
  uint16_t values[2];
  int values_num;
  const data_set_t *ds;
  int status;
  int i;

  if ((host == NULL) || (slave == NULL) || (data == NULL))
    return (EINVAL);

  ds = plugin_get_ds (data->type);
  if (ds == NULL)
  {
    ERROR ("Modbus plugin: Type \"%s\" is not defined.", data->type);
    return (-1);
  }

  if (ds->ds_num != 1)
  {
    ERROR ("Modbus plugin: The type \"%s\" has %i data sources. "
        "I can only handle data sets with only one data source.",
        data->type, ds->ds_num);
    return (-1);
  }

  if ((ds->ds[0].type != DS_TYPE_GAUGE)
      && (data->register_type != REG_TYPE_UINT32))
  {
    NOTICE ("Modbus plugin: The data source of type \"%s\" is %s, not gauge. "
        "This will most likely result in problems, because the register type "
        "is not UINT32.", data->type, DS_TYPE_TO_STRING (ds->ds[0].type));
  }

  memset (values, 0, sizeof (values));
  if ((data->register_type == REG_TYPE_UINT32)
      || (data->register_type == REG_TYPE_FLOAT))
    values_num = 2;
  else
    values_num = 1;

#if LEGACY_LIBMODBUS
  /* Version 2.0.3: Pass the connection struct as a pointer and pass the slave
   * id to each call of "read_holding_registers". */
# define modbus_read_registers(ctx, addr, nb, dest) \
  read_holding_registers (&(ctx), slave->id, (addr), (nb), (dest))
#else /* if !LEGACY_LIBMODBUS */
  /* Version 2.9.2: Set the slave id once before querying the registers. */
  status = modbus_set_slave (host->connection, slave->id);
  if (status != 0)
  {
    ERROR ("Modbus plugin: modbus_set_slave (%i) failed with status %i.",
        slave->id, status);
    return (-1);
  }
#endif

  for (i = 0; i < 2; i++)
  {
    status = modbus_read_registers (host->connection,
        /* start_addr = */ data->register_base,
        /* num_registers = */ values_num, /* buffer = */ values);
    if (status > 0)
      break;

    if (host->is_connected)
    {
#if LEGACY_LIBMODBUS
      modbus_close (&host->connection);
      host->is_connected = 0;
#else
      modbus_close (host->connection);
      modbus_free (host->connection);
      host->connection = NULL;
#endif
    }

    /* If we already tried reconnecting this round, give up. */
    if (host->have_reconnected)
    {
      ERROR ("Modbus plugin: modbus_read_registers (%s) failed. "
          "Reconnecting has already been tried. Giving up.", host->host);
      return (-1);
    }

    /* Maybe the device closed the connection during the waiting interval.
     * Try re-establishing the connection. */
    status = mb_init_connection (host);
    if (status != 0)
    {
      ERROR ("Modbus plugin: modbus_read_registers (%s) failed. "
          "While trying to reconnect, connecting to \"%s\" failed. "
          "Giving up.",
          host->host, host->node);
      return (-1);
    }

    DEBUG ("Modbus plugin: Re-established connection to %s", host->host);

    /* try again */
    continue;
  } /* for (i = 0, 1) */

  DEBUG ("Modbus plugin: mb_read_data: Success! "
      "modbus_read_registers returned with status %i.", status);

  if (data->register_type == REG_TYPE_FLOAT)
  {
    float float_value;
    value_t vt;

    float_value = mb_register_to_float (values[0], values[1]);
    DEBUG ("Modbus plugin: mb_read_data: "
        "Returned float value is %g", (double) float_value);

    CAST_TO_VALUE_T (ds, vt, float_value);
    mb_submit (host, slave, data, vt);
  }
  else if (data->register_type == REG_TYPE_UINT32)
  {
    uint32_t v32;
    value_t vt;

    v32 = (values[0] << 16) | values[1];
    DEBUG ("Modbus plugin: mb_read_data: "
        "Returned uint32 value is %"PRIu32, v32);

    CAST_TO_VALUE_T (ds, vt, v32);
    mb_submit (host, slave, data, vt);
  }
  else /* if (data->register_type == REG_TYPE_UINT16) */
  {
    value_t vt;

    DEBUG ("Modbus plugin: mb_read_data: "
        "Returned uint16 value is %"PRIu16, values[0]);

    CAST_TO_VALUE_T (ds, vt, values[0]);
    mb_submit (host, slave, data, vt);
  }

  return (0);
}