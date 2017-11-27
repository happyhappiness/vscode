static void set_environment (void) /* {{{ */
{
  char buffer[1024];

#ifdef HAVE_SETENV
  ssnprintf (buffer, sizeof (buffer), "%i", interval_g);
  setenv ("COLLECTD_INTERVAL", buffer, /* overwrite = */ 1);

  ssnprintf (buffer, sizeof (buffer), "%s", hostname_g);
  setenv ("COLLECTD_HOSTNAME", buffer, /* overwrite = */ 1);
#else
  ssnprintf (buffer, sizeof (buffer), "COLLECTD_INTERVAL=%i", interval_g);
  putenv (buffer);

  ssnprintf (buffer, sizeof (buffer), "COLLECTD_HOSTNAME=%s", hostname_g);
  putenv (buffer);
#endif
}