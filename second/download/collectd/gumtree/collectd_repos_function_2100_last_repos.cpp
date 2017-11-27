static int mb_submit(mb_host_t *host, mb_slave_t *slave, /* {{{ */
                     mb_data_t *data, value_t value) {
  value_list_t vl = VALUE_LIST_INIT;

  if ((host == NULL) || (slave == NULL) || (data == NULL))
    return EINVAL;

  if (host->interval == 0)
    host->interval = plugin_get_interval();

  if (slave->instance[0] == 0)
    snprintf(slave->instance, sizeof(slave->instance), "slave_%i", slave->id);

  vl.values = &value;
  vl.values_len = 1;
  vl.interval = host->interval;
  sstrncpy(vl.host, host->host, sizeof(vl.host));
  sstrncpy(vl.plugin, "modbus", sizeof(vl.plugin));
  sstrncpy(vl.plugin_instance, slave->instance, sizeof(vl.plugin_instance));
  sstrncpy(vl.type, data->type, sizeof(vl.type));
  sstrncpy(vl.type_instance, data->instance, sizeof(vl.type_instance));

  return plugin_dispatch_values(&vl);
}