static void ceph_daemons_print(void) {
  for (size_t i = 0; i < g_num_daemons; ++i) {
    ceph_daemon_print(g_daemons[i]);
  }
}