static int mb_config_add_slave(mb_host_t *host, oconfig_item_t *ci) /* {{{ */
{
  mb_slave_t *slave;
  int status;

  if ((host == NULL) || (ci == NULL))
    return (EINVAL);

  slave = realloc(host->slaves, sizeof(*slave) * (host->slaves_num + 1));
  if (slave == NULL)
    return (ENOMEM);
  host->slaves = slave;
  slave = host->slaves + host->slaves_num;
  memset(slave, 0, sizeof(*slave));
  slave->collect = NULL;

  status = cf_util_get_int(ci, &slave->id);
  if (status != 0)
    return (status);

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Instance", child->key) == 0)
      status = cf_util_get_string_buffer(child, slave->instance,
                                         sizeof(slave->instance));
    else if (strcasecmp("Collect", child->key) == 0) {
      char buffer[1024];
      status = cf_util_get_string_buffer(child, buffer, sizeof(buffer));
      if (status == 0)
        data_copy_by_name(&slave->collect, data_definitions, buffer);
      status = 0; /* continue after failure. */
    } else {
      ERROR("Modbus plugin: Unknown configuration option: %s", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  if ((status == 0) && (slave->collect == NULL))
    status = EINVAL;

  if (slave->id < 0)
    status = EINVAL;

  if (status == 0)
    host->slaves_num++;
  else /* if (status != 0) */
    data_free_all(slave->collect);

  return (status);
}