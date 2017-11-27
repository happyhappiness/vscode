const char *lcc_strerror(lcc_connection_t *c) /* {{{ */
{
  if (c == NULL)
    return "Invalid object";
  return c->errbuf;
}