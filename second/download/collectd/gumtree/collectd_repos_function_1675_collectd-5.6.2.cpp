static int ceph_init(void) {
#if defined(HAVE_SYS_CAPABILITY_H) && defined(CAP_DAC_OVERRIDE)
  if (check_capability(CAP_DAC_OVERRIDE) != 0) {
    if (getuid() == 0)
      WARNING("ceph plugin: Running collectd as root, but the "
              "CAP_DAC_OVERRIDE capability is missing. The plugin's read "
              "function will probably fail. Is your init system dropping "
              "capabilities?");
    else
      WARNING(
          "ceph plugin: collectd doesn't have the CAP_DAC_OVERRIDE "
          "capability. If you don't want to run collectd as root, try running "
          "\"setcap cap_dac_override=ep\" on the collectd binary.");
  }
#endif

  ceph_daemons_print();

  if (g_num_daemons < 1) {
    ERROR("ceph plugin: No daemons configured. See the \"Daemon\" config "
          "option.");
    return ENOENT;
  }

  return cconn_main_loop(ASOK_REQ_VERSION);
}