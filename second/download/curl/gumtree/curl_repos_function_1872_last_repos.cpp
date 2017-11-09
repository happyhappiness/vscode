static CURLcode ldap_disconnect(struct connectdata *conn, bool dead_connection)
{
  ldapconninfo *li = conn->proto.generic;
  (void) dead_connection;

  if(li) {
    if(li->ld) {
      ldap_unbind_ext(li->ld, NULL, NULL);
      li->ld = NULL;
    }
    conn->proto.generic = NULL;
    free(li);
  }
  return CURLE_OK;
}