int lcc_disconnect(lcc_connection_t *c) /* {{{ */
{
  if (c == NULL)
    return (-1);

  if (c->fh != NULL) {
    fclose(c->fh);
    c->fh = NULL;
  }

  free(c);
  return (0);
}