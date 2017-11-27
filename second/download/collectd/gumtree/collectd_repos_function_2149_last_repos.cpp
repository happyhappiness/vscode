static int xencpu_read(void) {
  cdtime_t now = cdtime();

  int rc, nr_cpus;

  rc = xc_getcpuinfo(xc_handle, num_cpus, cpu_info, &nr_cpus);
  if (rc < 0) {
    ERROR("xencpu: xc_getcpuinfo() Failed: %d %s\n", rc,
          xc_strerror(xc_handle, errno));
    return -1;
  }

  int status;
  for (int cpu = 0; cpu < nr_cpus; cpu++) {
    gauge_t rate = NAN;

    status = value_to_rate(&rate, (value_t){.derive = cpu_info[cpu].idletime},
                           DS_TYPE_DERIVE, now, &cpu_states[cpu]);
    if (status == 0) {
      submit_value(cpu, 100 - rate / 10000000);
    }
  }

  return 0;
}