int dpdk_helper_eal_config_parse(dpdk_helper_ctx_t *phc, oconfig_item_t *ci) {
  DPDK_HELPER_TRACE(phc->shm_name);

  if (phc == NULL) {
    ERROR("Invalid argument (phc)");
    return -EINVAL;
  }

  if (ci == NULL) {
    ERROR("Invalid argument (ci)");
    return -EINVAL;
  }

  int status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Coremask", child->key) == 0) {
      status = cf_util_get_string_buffer(child, phc->eal_config.coremask,
                                         sizeof(phc->eal_config.coremask));
      DEBUG("dpdk_common: EAL:Coremask %s", phc->eal_config.coremask);
    } else if (strcasecmp("MemoryChannels", child->key) == 0) {
      status =
          cf_util_get_string_buffer(child, phc->eal_config.memory_channels,
                                    sizeof(phc->eal_config.memory_channels));
      DEBUG("dpdk_common: EAL:Memory Channels %s",
            phc->eal_config.memory_channels);
    } else if (strcasecmp("SocketMemory", child->key) == 0) {
      status = cf_util_get_string_buffer(child, phc->eal_config.socket_memory,
                                         sizeof(phc->eal_config.socket_memory));
      DEBUG("dpdk_common: EAL:Socket memory %s", phc->eal_config.socket_memory);
    } else if (strcasecmp("FilePrefix", child->key) == 0) {
      char prefix[DATA_MAX_NAME_LEN];

      status = cf_util_get_string_buffer(child, prefix, sizeof(prefix));
      if (status == 0) {
        snprintf(phc->eal_config.file_prefix, DATA_MAX_NAME_LEN,
                 "/var/run/.%s_config", prefix);
        DEBUG("dpdk_common: EAL:File prefix %s", phc->eal_config.file_prefix);
      }
    } else if (strcasecmp("LogLevel", child->key) == 0) {
      status = cf_util_get_string_buffer(child, phc->eal_config.log_level,
                                         sizeof(phc->eal_config.log_level));
      DEBUG("dpdk_common: EAL:LogLevel %s", phc->eal_config.log_level);
    } else if (strcasecmp("RteDriverLibPath", child->key) == 0) {
      status = cf_util_get_string_buffer(
          child, phc->eal_config.rte_driver_lib_path,
          sizeof(phc->eal_config.rte_driver_lib_path));
      DEBUG("dpdk_common: EAL:RteDriverLibPath %s",
            phc->eal_config.rte_driver_lib_path);
    } else {
      ERROR("dpdk_common: Invalid '%s' configuration option", child->key);
      status = -EINVAL;
    }

    if (status != 0) {
      ERROR("dpdk_common: Parsing EAL configuration failed");
      break;
    }
  }

  return status;
}