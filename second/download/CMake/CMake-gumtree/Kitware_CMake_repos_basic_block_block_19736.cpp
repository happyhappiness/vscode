{
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