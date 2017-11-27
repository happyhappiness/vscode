static void load_submit(gauge_t snum, gauge_t mnum, gauge_t lnum) {
  int cores = 0;
  char errbuf[1024];

#ifdef _SC_NPROCESSORS_ONLN
  if (report_relative_load) {
    if ((cores = sysconf(_SC_NPROCESSORS_ONLN)) < 1) {
      WARNING("load: sysconf failed : %s",
              sstrerror(errno, errbuf, sizeof(errbuf)));
    }
  }
#endif
  if (cores > 0) {
    snum /= cores;
    mnum /= cores;
    lnum /= cores;
  }

  value_list_t vl = VALUE_LIST_INIT;
  value_t values[] = {
      {.gauge = snum}, {.gauge = mnum}, {.gauge = lnum},
  };

  vl.values = values;
  vl.values_len = STATIC_ARRAY_SIZE(values);

  sstrncpy(vl.plugin, "load", sizeof(vl.plugin));
  sstrncpy(vl.type, "load", sizeof(vl.type));

  if (cores > 0) {
    sstrncpy(vl.type_instance, "relative", sizeof(vl.type_instance));
  }

  plugin_dispatch_values(&vl);
}