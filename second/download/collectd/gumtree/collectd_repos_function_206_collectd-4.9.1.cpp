static void set_environment (void) /* {{{ */
{
  char buffer[1024];

  ssnprintf (buffer, sizeof (buffer), "%i", interval_g);
  setenv ("COLLECTD_INTERVAL", buffer, /* overwrite = */ 1);

  ssnprintf (buffer, sizeof (buffer), "%s", hostname_g);
  setenv ("COLLECTD_HOSTNAME", buffer, /* overwrite = */ 1);
}