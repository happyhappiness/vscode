static int dpdk_helper_init_eal(void) {
  g_configuration->helper_status = DPDK_HELPER_INITIALIZING_EAL;
  char *argp[(g_configuration->eal_argc) + 1];
  int i = 0;

  argp[i++] = "collectd-dpdk";
  if (strcasecmp(g_configuration->coremask, "") != 0) {
    argp[i++] = "-c";
    argp[i++] = g_configuration->coremask;
  }
  if (strcasecmp(g_configuration->memory_channels, "") != 0) {
    argp[i++] = "-n";
    argp[i++] = g_configuration->memory_channels;
  }
  if (strcasecmp(g_configuration->socket_memory, "") != 0) {
    argp[i++] = "--socket-mem";
    argp[i++] = g_configuration->socket_memory;
  }
  if (strcasecmp(g_configuration->file_prefix, "") != 0 &&
      strcasecmp(g_configuration->file_prefix, DPDK_DEFAULT_RTE_CONFIG) != 0) {
    argp[i++] = "--file-prefix";
    argp[i++] = g_configuration->file_prefix;
  }
  if (strcasecmp(g_configuration->process_type, "") != 0) {
    argp[i++] = "--proc-type";
    argp[i++] = g_configuration->process_type;
  }
  g_configuration->eal_argc = i;

  g_configuration->eal_initialized = 1;
  int ret = rte_eal_init(g_configuration->eal_argc, argp);
  if (ret < 0) {
    g_configuration->eal_initialized = 0;
    return ret;
  }
  return 0;
}