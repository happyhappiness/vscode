static void cpu_submit(const domain_t *dom, unsigned long long cpuTime_new) {

  if (!dom)
    return;

  if (extra_stats & ex_stats_cpu_util) {
    /* Computing %CPU requires 2 samples of cpuTime */
    if (dom->info.cpuTime != 0 && cpuTime_new != 0) {

      submit(dom->ptr, "percent", "virt_cpu_total",
             &(value_t){.gauge = cpu_ns_to_percent(
                            nodeinfo.cpus, dom->info.cpuTime, cpuTime_new)},
             1);
    }
  }

  submit(dom->ptr, "virt_cpu_total", NULL, &(value_t){.derive = cpuTime_new},
         1);
}