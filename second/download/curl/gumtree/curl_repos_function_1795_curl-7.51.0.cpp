static CURLcode ldap_done(struct connectdata *conn, CURLcode res,
                          bool premature)
{
  ldapreqinfo *lr = conn->data->req.protop;

  (void)res;
  (void)premature;

  if(lr) {
    /* if there was a search in progress, abandon it */
    if(lr->msgid) {
      ldapconninfo *li = conn->proto.generic;
      ldap_abandon_ext(li->ld, lr->msgid, NULL, NULL);
      lr->msgid = 0;
    }
    conn->data->req.protop = NULL;
    free(lr);
  }

  return CURLE_OK;
}