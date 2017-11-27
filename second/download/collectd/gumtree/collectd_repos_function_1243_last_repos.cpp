static int huge_read(void) {
  static const char sys_mm_hugepages[] = "/sys/kernel/mm/hugepages";

  if (g_flag_rpt_mm) {
    if (read_syshugepages(sys_mm_hugepages, "mm") != 0) {
      return -1;
    }
  }
  if (g_flag_rpt_numa) {
    if (read_nodes() != 0) {
      return -1;
    }
  }

  return 0;
}