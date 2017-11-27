static int cpu_is_not_present(unsigned int cpu) {
  return !CPU_ISSET_S(cpu, cpu_present_setsize, cpu_present_set);
}