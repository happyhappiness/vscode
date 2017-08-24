((ksp = kstat_lookup(kc, (char*) "cpu_info", lookup_instance, NULL))) {
    lookup_instance++;
  }