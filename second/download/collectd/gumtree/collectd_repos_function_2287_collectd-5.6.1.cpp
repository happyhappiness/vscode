static int lcc_send (lcc_connection_t *c, const char *command) /* {{{ */
{
  int status;

  lcc_tracef ("send:    --> %s\n", command);

  status = fprintf (c->fh, "%s\r\n", command);
  if (status < 0)
  {
    lcc_set_errno (c, errno);
    return (-1);
  }
  fflush(c->fh);

  return (0);
}