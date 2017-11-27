static int cpufreq_read(void) {
  for (int i = 0; i < num_cpu; i++) {
    char filename[PATH_MAX];
    ssnprintf(filename, sizeof(filename),
              "/sys/devices/system/cpu/cpu%d/cpufreq/scaling_cur_freq", i);

    value_t v;
    if (parse_value_file(filename, &v, DS_TYPE_GAUGE) != 0) {
      WARNING("cpufreq plugin: Reading \"%s\" failed.", filename);
      continue;
    }

    /* convert kHz to Hz */
    v.gauge *= 1000.0;

    cpufreq_submit(i, v);
  }

  return (0);
}