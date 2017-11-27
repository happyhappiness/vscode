static int ping_init (void) /* {{{ */
{
  if (hostlist_head == NULL)
  {
    NOTICE ("ping plugin: No hosts have been configured.");
    return (-1);
  }

  if (ping_timeout > ping_interval)
  {
    ping_timeout = 0.9 * ping_interval;
    WARNING ("ping plugin: Timeout is greater than interval. "
        "Will use a timeout of %gs.", ping_timeout);
  }

#if defined(HAVE_SYS_CAPABILITY_H) && defined(CAP_NET_RAW)
  if (check_capability (CAP_NET_RAW) != 0)
  {
    if (getuid () == 0)
      WARNING ("ping plugin: Running collectd as root, but the CAP_NET_RAW "
          "capability is missing. The plugin's read function will probably "
          "fail. Is your init system dropping capabilities?");
    else
      WARNING ("ping plugin: collectd doesn't have the CAP_NET_RAW capability. "
          "If you don't want to run collectd as root, try running \"setcap "
          "cap_net_raw=ep\" on the collectd binary.");
  }
#endif

  return (start_thread ());
}