{
  int           lookup_instance;
  kstat_ctl_t   *kc;
  kstat_t       *ksp;
  kstat_named_t *knp;
  uv_cpu_info_t* cpu_info;

  kc = kstat_open();
  if (kc == NULL)
    return -EPERM;

  /* Get count of cpus */
  lookup_instance = 0;
  while ((ksp = kstat_lookup(kc, (char*) "cpu_info", lookup_instance, NULL))) {
    lookup_instance++;
  }

  *cpu_infos = uv__malloc(lookup_instance * sizeof(**cpu_infos));
  if (!(*cpu_infos)) {
    kstat_close(kc);
    return -ENOMEM;
  }

  *count = lookup_instance;

  cpu_info = *cpu_infos;
  lookup_instance = 0;
  while ((ksp = kstat_lookup(kc, (char*) "cpu_info", lookup_instance, NULL))) {
    if (kstat_read(kc, ksp, NULL) == -1) {
      cpu_info->speed = 0;
      cpu_info->model = NULL;
    } else {
      knp = kstat_data_lookup(ksp, (char*) "clock_MHz");
      assert(knp->data_type == KSTAT_DATA_INT32 ||
             knp->data_type == KSTAT_DATA_INT64);
      cpu_info->speed = (knp->data_type == KSTAT_DATA_INT32) ? knp->value.i32
                                                             : knp->value.i64;

      knp = kstat_data_lookup(ksp, (char*) "brand");
      assert(knp->data_type == KSTAT_DATA_STRING);
      cpu_info->model = uv__strdup(KSTAT_NAMED_STR_PTR(knp));
    }

    lookup_instance++;
    cpu_info++;
  }

  cpu_info = *cpu_infos;
  lookup_instance = 0;
  for (;;) {
    ksp = kstat_lookup(kc, (char*) "cpu", lookup_instance, (char*) "sys");

    if (ksp == NULL)
      break;

    if (kstat_read(kc, ksp, NULL) == -1) {
      cpu_info->cpu_times.user = 0;
      cpu_info->cpu_times.nice = 0;
      cpu_info->cpu_times.sys = 0;
      cpu_info->cpu_times.idle = 0;
      cpu_info->cpu_times.irq = 0;
    } else {
      knp = kstat_data_lookup(ksp, (char*) "cpu_ticks_user");
      assert(knp->data_type == KSTAT_DATA_UINT64);
      cpu_info->cpu_times.user = knp->value.ui64;

      knp = kstat_data_lookup(ksp, (char*) "cpu_ticks_kernel");
      assert(knp->data_type == KSTAT_DATA_UINT64);
      cpu_info->cpu_times.sys = knp->value.ui64;

      knp = kstat_data_lookup(ksp, (char*) "cpu_ticks_idle");
      assert(knp->data_type == KSTAT_DATA_UINT64);
      cpu_info->cpu_times.idle = knp->value.ui64;

      knp = kstat_data_lookup(ksp, (char*) "intr");
      assert(knp->data_type == KSTAT_DATA_UINT64);
      cpu_info->cpu_times.irq = knp->value.ui64;
      cpu_info->cpu_times.nice = 0;
    }

    lookup_instance++;
    cpu_info++;
  }

  kstat_close(kc);

  return 0;
}