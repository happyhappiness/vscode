static int dpdk_helper_eal_init(dpdk_helper_ctx_t *phc) {
  phc->status = DPDK_HELPER_INITIALIZING_EAL;
  DPDK_CHILD_LOG("%s:%s:%d DPDK_HELPER_INITIALIZING_EAL (start)\n",
                 phc->shm_name, __FUNCTION__, __LINE__);

  char *argp[DPDK_EAL_ARGC * 2 + 1];
  int argc = 0;

  /* EAL config must be initialized */
  assert(phc->eal_config.coremask[0] != 0);
  assert(phc->eal_config.memory_channels[0] != 0);
  assert(phc->eal_config.file_prefix[0] != 0);

  argp[argc++] = "collectd-dpdk";

  argp[argc++] = "-c";
  argp[argc++] = phc->eal_config.coremask;

  argp[argc++] = "-n";
  argp[argc++] = phc->eal_config.memory_channels;

  if (strcasecmp(phc->eal_config.socket_memory, "") != 0) {
    argp[argc++] = "--socket-mem";
    argp[argc++] = phc->eal_config.socket_memory;
  }

  if (strcasecmp(phc->eal_config.file_prefix, DPDK_DEFAULT_RTE_CONFIG) != 0) {
    argp[argc++] = "--file-prefix";
    argp[argc++] = phc->eal_config.file_prefix;
  }

  argp[argc++] = "--proc-type";
  argp[argc++] = "secondary";

  if (strcasecmp(phc->eal_config.log_level, "") != 0) {
    argp[argc++] = "--log-level";
    argp[argc++] = phc->eal_config.log_level;
  }
  if (strcasecmp(phc->eal_config.rte_driver_lib_path, "") != 0) {
    argp[argc++] = "-d";
    argp[argc++] = phc->eal_config.rte_driver_lib_path;
  }

  assert(argc <= (DPDK_EAL_ARGC * 2 + 1));

  int ret = rte_eal_init(argc, argp);

  if (ret < 0) {

    phc->eal_initialized = 0;

    DPDK_CHILD_LOG("dpdk_helper_eal_init: ERROR initializing EAL ret=%d\n",
                   ret);

    printf("dpdk_helper_eal_init: EAL arguments: ");
    for (int i = 0; i < argc; i++) {
      printf("%s ", argp[i]);
    }
    printf("\n");

    return ret;
  }

  phc->eal_initialized = 1;

  DPDK_CHILD_LOG("%s:%s:%d DPDK_HELPER_INITIALIZING_EAL (done)\n",
                 phc->shm_name, __FUNCTION__, __LINE__);

  return 0;
}