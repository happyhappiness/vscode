static int exec_init (void) /* {{{ */
{
  struct sigaction sa = {
    .sa_handler = sigchld_handler
  };

  sigaction (SIGCHLD, &sa, NULL);

#if defined(HAVE_SYS_CAPABILITY_H) && defined(CAP_SETUID) && defined(CAP_SETGID)
  if ((check_capability (CAP_SETUID) != 0) ||
      (check_capability (CAP_SETGID) != 0))
  {
    if (getuid () == 0)
      WARNING ("exec plugin: Running collectd as root, but the CAP_SETUID "
          "or CAP_SETGID capabilities are missing. The plugin's read function "
          "will probably fail. Is your init system dropping capabilities?");
    else
      WARNING ("exec plugin: collectd doesn't have the CAP_SETUID or "
          "CAP_SETGID capabilities. If you don't want to run collectd as root, "
          "try running \"setcap 'cap_setuid=ep cap_setgid=ep'\" on the "
          "collectd binary.");
  }
#endif

  return (0);
}