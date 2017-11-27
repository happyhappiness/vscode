static const char *cx_host(cx_t *db) /* {{{ */
{
  if (db->host == NULL)
    return hostname_g;
  return db->host;
}