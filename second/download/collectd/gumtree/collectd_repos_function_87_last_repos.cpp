static void vcpu_pin_submit(virDomainPtr dom, int max_cpus, int vcpu,
                            unsigned char *cpu_maps, int cpu_map_len) {
  for (int cpu = 0; cpu < max_cpus; ++cpu) {
    char type_instance[DATA_MAX_NAME_LEN];
    _Bool is_set = VIR_CPU_USABLE(cpu_maps, cpu_map_len, vcpu, cpu) ? 1 : 0;

    snprintf(type_instance, sizeof(type_instance), "vcpu_%d-cpu_%d", vcpu, cpu);
    submit(dom, "cpu_affinity", type_instance, &(value_t){.gauge = is_set}, 1);
  }
}