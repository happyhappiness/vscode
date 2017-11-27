static int rdt_preinit(void) {
  int ret;

  if (g_rdt != NULL) {
    /* already initialized if config callback was called before init callback */
    return (0);
  }

  g_rdt = calloc(1, sizeof(*g_rdt));
  if (g_rdt == NULL) {
    ERROR(RDT_PLUGIN ": Failed to allocate memory for rdt context.");
    return (-ENOMEM);
  }

  /* In case previous instance of the application was not closed properly
   * call fini and ignore return code. */
  pqos_fini();

  /* TODO:
   * stdout should not be used here. Will be reworked when support of log
   * callback is added to PQoS library.
  */
  ret = pqos_init(&(struct pqos_config){.fd_log = STDOUT_FILENO});
  if (ret != PQOS_RETVAL_OK) {
    ERROR(RDT_PLUGIN ": Error initializing PQoS library!");
    goto rdt_preinit_error1;
  }

  ret = pqos_cap_get(&g_rdt->pqos_cap, &g_rdt->pqos_cpu);
  if (ret != PQOS_RETVAL_OK) {
    ERROR(RDT_PLUGIN ": Error retrieving PQoS capabilities.");
    goto rdt_preinit_error2;
  }

  ret = pqos_cap_get_type(g_rdt->pqos_cap, PQOS_CAP_TYPE_MON, &g_rdt->cap_mon);
  if (ret == PQOS_RETVAL_PARAM) {
    ERROR(RDT_PLUGIN ": Error retrieving monitoring capabilities.");
    goto rdt_preinit_error2;
  }

  if (g_rdt->cap_mon == NULL) {
    ERROR(
        RDT_PLUGIN
        ": Monitoring capability not detected. Nothing to do for the plugin.");
    goto rdt_preinit_error2;
  }

  return (0);

rdt_preinit_error2:
  pqos_fini();

rdt_preinit_error1:

  sfree(g_rdt);

  return (-1);
}