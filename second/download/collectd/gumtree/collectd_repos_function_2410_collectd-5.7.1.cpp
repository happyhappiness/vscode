static int lcc_set_errno(lcc_connection_t *c, int err) /* {{{ */
{
  if (c == NULL)
    return (-1);

  sstrerror(err, c->errbuf, sizeof(c->errbuf));
  c->errbuf[sizeof(c->errbuf) - 1] = 0;

  return (0);
}