static int parse_line (char *buffer) /* {{{ */
{
  if (strncasecmp ("PUTVAL", buffer, strlen ("PUTVAL")) == 0)
    return (handle_putval (stdout, buffer));
  else if (strncasecmp ("PUTNOTIF", buffer, strlen ("PUTNOTIF")) == 0)
    return (handle_putnotif (stdout, buffer));
  else
  {
    /* For backwards compatibility */
    char tmp[1220];
    /* Let's annoy the user a bit.. */
    INFO ("exec plugin: Prepending `PUTVAL' to this line: %s", buffer);
    ssnprintf (tmp, sizeof (tmp), "PUTVAL %s", buffer);
    return (handle_putval (stdout, tmp));
  }
}