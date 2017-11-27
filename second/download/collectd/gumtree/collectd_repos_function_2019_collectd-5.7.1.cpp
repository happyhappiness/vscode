static int xencpu_init(void) {
  xc_handle = xc_interface_open(XC_INTERFACE_INIT_ARGS);
  if (!xc_handle) {
    ERROR("xencpu: xc_interface_open() failed");
    return (-1);
  }

  xc_physinfo_t *physinfo;

  physinfo = calloc(1, sizeof(xc_physinfo_t));
  if (physinfo == NULL) {
    ERROR("xencpu plugin: calloc() for physinfo failed.");
    xc_interface_close(xc_handle);
    return (ENOMEM);
  }

  if (xc_physinfo(xc_handle, physinfo) < 0) {
    ERROR("xencpu plugin: xc_physinfo() failed");
    xc_interface_close(xc_handle);
    free(physinfo);
    return (-1);
  }

  num_cpus = physinfo->nr_cpus;
  free(physinfo);

  INFO("xencpu plugin: Found %" PRIu32 " processors.", num_cpus);

  cpu_info = calloc(num_cpus, sizeof(xc_cpuinfo_t));
  if (cpu_info == NULL) {
    ERROR("xencpu plugin: calloc() for num_cpus failed.");
    xc_interface_close(xc_handle);
    return (ENOMEM);
  }

  cpu_states = calloc(num_cpus, sizeof(value_to_rate_state_t));
  if (cpu_states == NULL) {
    ERROR("xencpu plugin: calloc() for cpu_states failed.");
    xc_interface_close(xc_handle);
    free(cpu_info);
    return (ENOMEM);
  }

  return (0);
}