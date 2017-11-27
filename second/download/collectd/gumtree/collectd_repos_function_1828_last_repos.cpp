static const char *cx_host(const cx_t *db) /* {{{ */
{
  if (db->host == NULL)
    return hostname_g;
  return db->host;
}