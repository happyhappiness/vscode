static int _ldap_url_parse (const struct connectdata *conn,
                            LDAPURLDesc **ludpp)
{
  LDAPURLDesc *ludp = calloc(sizeof(*ludp), 1);
  int rc;

  *ludpp = NULL;
  if (!ludp)
     return LDAP_NO_MEMORY;

  rc = _ldap_url_parse2 (conn, ludp);
  if (rc != LDAP_SUCCESS) {
    _ldap_free_urldesc(ludp);
    ludp = NULL;
  }
  *ludpp = ludp;
  return (rc);
}