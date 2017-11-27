static int allocate_counters(struct thread_data **threads,
                             struct core_data **cores,
                             struct pkg_data **packages) {
  unsigned int total_threads, total_cores;

  if ((topology.num_threads == 0) || (topology.num_cores == 0) ||
      (topology.num_packages == 0)) {
    ERROR(
        "turbostat plugin: Invalid topology: %u threads, %u cores, %u packages",
        topology.num_threads, topology.num_cores, topology.num_packages);
    return -1;
  }

  total_threads =
      topology.num_threads * topology.num_cores * topology.num_packages;
  *threads = calloc(total_threads, sizeof(struct thread_data));
  if (*threads == NULL) {
    ERROR("turbostat plugin: calloc failed");
    return -1;
  }

  for (unsigned int i = 0; i < total_threads; ++i)
    (*threads)[i].cpu_id = topology.max_cpu_id + 1;

  total_cores = topology.num_cores * topology.num_packages;
  *cores = calloc(total_cores, sizeof(struct core_data));
  if (*cores == NULL) {
    ERROR("turbostat plugin: calloc failed");
    sfree(threads);
    return -1;
  }

  *packages = calloc(topology.num_packages, sizeof(struct pkg_data));
  if (*packages == NULL) {
    ERROR("turbostat plugin: calloc failed");
    sfree(cores);
    sfree(threads);
    return -1;
  }

  return 0;
}