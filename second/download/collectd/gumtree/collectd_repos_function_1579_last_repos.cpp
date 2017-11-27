static int smart_init(void) {
#if defined(HAVE_SYS_CAPABILITY_H) && defined(CAP_SYS_RAWIO)
  if (check_capability(CAP_SYS_RAWIO) != 0) {
    if (getuid() == 0)
      WARNING("smart plugin: Running collectd as root, but the "
              "CAP_SYS_RAWIO capability is missing. The plugin's read "
              "function will probably fail. Is your init system dropping "
              "capabilities?");
    else
      WARNING("smart plugin: collectd doesn't have the CAP_SYS_RAWIO "
              "capability. If you don't want to run collectd as root, try "
              "running \"setcap cap_sys_rawio=ep\" on the collectd binary.");
  }
#endif
  return 0;
}