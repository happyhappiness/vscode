(kstat_read(kc, ksp, NULL) == -1) {
    *uptime = -1;
  } else {
    knp = (kstat_named_t*)  kstat_data_lookup(ksp, (char*) "clk_intr");
    *uptime = knp->value.ul / hz;
  }