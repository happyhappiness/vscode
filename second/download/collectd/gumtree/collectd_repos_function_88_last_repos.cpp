static int get_vcpu_stats(virDomainPtr domain, unsigned short nr_virt_cpu) {
  int max_cpus = VIR_NODEINFO_MAXCPUS(nodeinfo);
  int cpu_map_len = VIR_CPU_MAPLEN(max_cpus);

  virVcpuInfoPtr vinfo = calloc(nr_virt_cpu, sizeof(vinfo[0]));
  if (vinfo == NULL) {
    ERROR(PLUGIN_NAME " plugin: malloc failed.");
    return -1;
  }

  unsigned char *cpumaps = calloc(nr_virt_cpu, cpu_map_len);
  if (cpumaps == NULL) {
    ERROR(PLUGIN_NAME " plugin: malloc failed.");
    sfree(vinfo);
    return -1;
  }

  int status =
      virDomainGetVcpus(domain, vinfo, nr_virt_cpu, cpumaps, cpu_map_len);
  if (status < 0) {
    ERROR(PLUGIN_NAME " plugin: virDomainGetVcpus failed with status %i.",
          status);
    sfree(cpumaps);
    sfree(vinfo);
    return status;
  }

  for (int i = 0; i < nr_virt_cpu; ++i) {
    vcpu_submit(vinfo[i].cpuTime, domain, vinfo[i].number, "virt_vcpu");
    if (extra_stats & ex_stats_vcpupin)
      vcpu_pin_submit(domain, max_cpus, i, cpumaps, cpu_map_len);
  }

  sfree(cpumaps);
  sfree(vinfo);
  return 0;
}