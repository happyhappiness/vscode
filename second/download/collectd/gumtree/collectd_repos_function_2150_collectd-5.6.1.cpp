static const char *cj_host (cj_t *db) /* {{{ */
{
  if ((db->host == NULL)
      || (strcmp ("", db->host) == 0)
      || (strcmp (CJ_DEFAULT_HOST, db->host) == 0))
    return hostname_g;
  return db->host;
}