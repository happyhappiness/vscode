static int _ldap_url_parse2 (const struct connectdata *conn, LDAPURLDesc *ludp)
{
  char *p, *q;
  int i;

  if (!conn->path || conn->path[0] != '/' ||
      !checkprefix(conn->protostr, conn->data->change.url))
     return LDAP_INVALID_SYNTAX;

  ludp->lud_scope = LDAP_SCOPE_BASE;
  ludp->lud_port  = conn->remote_port;
  ludp->lud_host  = conn->host.name;

  /* parse DN (Distinguished Name).
   */
  ludp->lud_dn = strdup(conn->path+1);
  if (!ludp->lud_dn)
     return LDAP_NO_MEMORY;

  p = strchr(ludp->lud_dn, '?');
  LDAP_TRACE (("DN '%.*s'\n", p ? (size_t)(p-ludp->lud_dn) : strlen(ludp->lud_dn),
               ludp->lud_dn));

  if (!p)
     goto success;

  *p++ = '\0';

  /* parse attributes. skip "??".
   */
  q = strchr(p, '?');
  if (q)
     *q++ = '\0';

  if (*p && *p != '?') {
    ludp->lud_attrs = split_str(p);
    if (!ludp->lud_attrs)
       return LDAP_NO_MEMORY;

    for (i = 0; ludp->lud_attrs[i]; i++)
        LDAP_TRACE (("attr[%d] '%s'\n", i, ludp->lud_attrs[i]));
  }

  p = q;
  if (!p)
     goto success;

  /* parse scope. skip "??"
   */
  q = strchr(p, '?');
  if (q)
     *q++ = '\0';

  if (*p && *p != '?') {
    ludp->lud_scope = str2scope(p);
    if (ludp->lud_scope == -1)
       return LDAP_INVALID_SYNTAX;
    LDAP_TRACE (("scope %d\n", ludp->lud_scope));
  }

  p = q;
  if (!p)
     goto success;

  /* parse filter
   */
  q = strchr(p, '?');
  if (q)
     *q++ = '\0';
  if (!*p)
     return LDAP_INVALID_SYNTAX;

  ludp->lud_filter = p;
  LDAP_TRACE (("filter '%s'\n", ludp->lud_filter));

  p = q;
  if (!p)
     goto success;

  /* parse extensions
   */
  ludp->lud_exts = split_str(p);
  if (!ludp->lud_exts)
     return LDAP_NO_MEMORY;

  for (i = 0; ludp->lud_exts[i]; i++)
      LDAP_TRACE (("exts[%d] '%s'\n", i, ludp->lud_exts[i]));

success:
  if (!unescape_elements(ludp))
     return LDAP_NO_MEMORY;
  return LDAP_SUCCESS;
}