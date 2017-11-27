static int parse_line(char *buffer) /* {{{ */
{
  if (strncasecmp("PUTVAL", buffer, strlen("PUTVAL")) == 0)
    return (cmd_handle_putval(stdout, buffer));
  else if (strncasecmp("PUTNOTIF", buffer, strlen("PUTNOTIF")) == 0)
    return (handle_putnotif(stdout, buffer));
  else {
    ERROR("exec plugin: Unable to parse command, ignoring line: \"%s\"",
          buffer);
    return (-1);
  }
}