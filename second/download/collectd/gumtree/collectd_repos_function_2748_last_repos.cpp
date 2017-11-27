static void update_kstat(void) {
  if (kc == NULL) {
    if ((kc = kstat_open()) == NULL)
      ERROR("Unable to open kstat control structure");
  } else {
    kid_t kid;
    kid = kstat_chain_update(kc);
    if (kid > 0) {
      INFO("kstat chain has been updated");
      plugin_init_all();
    } else if (kid < 0)
      ERROR("kstat chain update failed");
    /* else: everything works as expected */
  }

  return;
}