static int c_lvm_init(void) {
#if defined(HAVE_SYS_CAPABILITY_H) && defined(CAP_SYS_ADMIN)
  if (check_capability(CAP_SYS_ADMIN) != 0) {
    if (getuid() == 0)
      WARNING("lvm plugin: Running collectd as root, but the "
              "CAP_SYS_ADMIN capability is missing. The plugin's read "
              "function will probably fail. Is your init system dropping "
              "capabilities?");
    else
      WARNING("lvm plugin: collectd doesn't have the CAP_SYS_ADMIN "
              "capability. If you don't want to run collectd as root, try "
              "running \"setcap cap_sys_admin=ep\" on the collectd binary.");
  }
#endif
  return 0;
}