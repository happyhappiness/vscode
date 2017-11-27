static int mark_cpu_present(unsigned int cpu) {
  CPU_SET_S(cpu, cpu_present_setsize, cpu_present_set);
  return 0;
}