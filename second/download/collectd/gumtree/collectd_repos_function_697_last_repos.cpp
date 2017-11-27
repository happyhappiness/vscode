static int read_fork_rate(void) {
  extern kstat_ctl_t *kc;
  derive_t result = 0;

  if (kc == NULL)
    return -1;

  for (kstat_t *ksp_chain = kc->kc_chain; ksp_chain != NULL;
       ksp_chain = ksp_chain->ks_next) {
    if ((strcmp(ksp_chain->ks_module, "cpu") == 0) &&
        (strcmp(ksp_chain->ks_name, "sys") == 0) &&
        (strcmp(ksp_chain->ks_class, "misc") == 0)) {
      long long tmp;

      kstat_read(kc, ksp_chain, NULL);

      tmp = get_kstat_value(ksp_chain, "nthreads");
      if (tmp != -1LL)
        result += tmp;
    }
  }

  ps_submit_fork_rate(result);
  return 0;
}