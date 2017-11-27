static int dpdk_config(oconfig_item_t *ci) {
  int port_counter = 0;
  /* Allocate g_configuration and
   * initialize a POSIX SHared Memory (SHM) object.
   */
  int err = dpdk_shm_init(sizeof(dpdk_config_t));
  if (err) {
    char errbuf[ERR_BUF_SIZE];
    ERROR("dpdkstat: error in shm_init, %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  /* Set defaults for config, overwritten by loop if config item exists */
  dpdk_config_init_default();

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Coremask", child->key) == 0) {
      cf_util_get_string_buffer(child, g_configuration->coremask,
                                sizeof(g_configuration->coremask));
      DEBUG("dpdkstat:COREMASK %s ", g_configuration->coremask);
    } else if (strcasecmp("MemoryChannels", child->key) == 0) {
      cf_util_get_string_buffer(child, g_configuration->memory_channels,
                                sizeof(g_configuration->memory_channels));
      DEBUG("dpdkstat:Memory Channels %s ", g_configuration->memory_channels);
    } else if (strcasecmp("SocketMemory", child->key) == 0) {
      cf_util_get_string_buffer(child, g_configuration->socket_memory,
                                sizeof(g_configuration->memory_channels));
      DEBUG("dpdkstat: socket mem %s ", g_configuration->socket_memory);
    } else if (strcasecmp("ProcessType", child->key) == 0) {
      cf_util_get_string_buffer(child, g_configuration->process_type,
                                sizeof(g_configuration->process_type));
      DEBUG("dpdkstat: proc type %s ", g_configuration->process_type);
    } else if ((strcasecmp("FilePrefix", child->key) == 0) &&
               (child->values[0].type == OCONFIG_TYPE_STRING)) {
      ssnprintf(g_configuration->file_prefix, DATA_MAX_NAME_LEN,
                "/var/run/.%s_config", child->values[0].value.string);
      DEBUG("dpdkstat: file prefix %s ", g_configuration->file_prefix);
    } else if ((strcasecmp("EnabledPortMask", child->key) == 0) &&
               (child->values[0].type == OCONFIG_TYPE_NUMBER)) {
      g_configuration->enabled_port_mask =
          (uint32_t)child->values[0].value.number;
      DEBUG("dpdkstat: Enabled Port Mask %u",
            g_configuration->enabled_port_mask);
    } else if (strcasecmp("PortName", child->key) == 0) {
      cf_util_get_string_buffer(
          child, g_configuration->port_name[port_counter],
          sizeof(g_configuration->port_name[port_counter]));
      DEBUG("dpdkstat: Port %d Name: %s ", port_counter,
            g_configuration->port_name[port_counter]);
      port_counter++;
    } else {
      WARNING("dpdkstat: The config option \"%s\" is unknown.", child->key);
    }
  }                 /* End for (int i = 0; i < ci->children_num; i++)*/
  g_configured = 1; /* Bypass configuration in dpdk_shm_init(). */

  return 0;
}