static void dpdk_config_init_default(void) {
  g_configuration->interval = plugin_get_interval();
  if (g_configuration->interval == cf_get_default_interval())
    WARNING("dpdkstat: No time interval was configured, default value %" PRIu64
            " ms is set",
            CDTIME_T_TO_MS(g_configuration->interval));
  /* Default is all ports enabled */
  g_configuration->enabled_port_mask = ~0;
  g_configuration->eal_argc = DPDK_MAX_ARGC;
  g_configuration->eal_initialized = 0;
  ssnprintf(g_configuration->coremask, DATA_MAX_NAME_LEN, "%s", "0xf");
  ssnprintf(g_configuration->memory_channels, DATA_MAX_NAME_LEN, "%s", "1");
  ssnprintf(g_configuration->process_type, DATA_MAX_NAME_LEN, "%s",
            "secondary");
  ssnprintf(g_configuration->file_prefix, DATA_MAX_NAME_LEN, "%s",
            DPDK_DEFAULT_RTE_CONFIG);

  for (int i = 0; i < RTE_MAX_ETHPORTS; i++)
    g_configuration->port_name[i][0] = 0;
}