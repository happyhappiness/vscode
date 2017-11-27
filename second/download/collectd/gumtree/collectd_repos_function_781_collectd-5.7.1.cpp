static int iptables_init(void) {
#if defined(HAVE_SYS_CAPABILITY_H) && defined(CAP_NET_ADMIN)
  if (check_capability(CAP_NET_ADMIN) != 0) {
    if (getuid() == 0)
      WARNING("iptables plugin: Running collectd as root, but the "
              "CAP_NET_ADMIN capability is missing. The plugin's read "
              "function will probably fail. Is your init system dropping "
              "capabilities?");
    else
      WARNING("iptables plugin: collectd doesn't have the CAP_NET_ADMIN "
              "capability. If you don't want to run collectd as root, try "
              "running \"setcap cap_net_admin=ep\" on the collectd binary.");
  }
#endif
  return (0);
}