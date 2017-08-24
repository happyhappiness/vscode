{
  ldapconninfo *li = conn->proto.generic;
  ldapreqinfo *lr;
  CURLcode status = CURLE_OK;
  int rc = 0;
  LDAPURLDesc *ludp = NULL;
  int msgid;
  struct Curl_easy *data=conn->data;

  connkeep(conn, "OpenLDAP do");

  infof(data, "LDAP local: %s\n", data->change.url);

  rc = ldap_url_parse(data->change.url, &ludp);
  if(rc != LDAP_URL_SUCCESS) {
    const char *msg = "url parsing problem";
    status = CURLE_URL_MALFORMAT;
    if(rc > LDAP_URL_SUCCESS && rc <= LDAP_URL_ERR_BADEXTS) {
      if(rc == LDAP_URL_ERR_MEM)
        status = CURLE_OUT_OF_MEMORY;
      msg = url_errs[rc];
    }
    failf(conn->data, "LDAP local: %s", msg);
    return status;
  }

  rc = ldap_search_ext(li->ld, ludp->lud_dn, ludp->lud_scope,
                       ludp->lud_filter, ludp->lud_attrs, 0,
                       NULL, NULL, NULL, 0, &msgid);
  ldap_free_urldesc(ludp);
  if(rc != LDAP_SUCCESS) {
    failf(data, "LDAP local: ldap_search_ext %s", ldap_err2string(rc));
    return CURLE_LDAP_SEARCH_FAILED;
  }
  lr = calloc(1, sizeof(ldapreqinfo));
  if(!lr)
    return CURLE_OUT_OF_MEMORY;
  lr->msgid = msgid;
  data->req.protop = lr;
  Curl_setup_transfer(conn, FIRSTSOCKET, -1, FALSE, NULL, -1, NULL);
  *done = TRUE;
  return CURLE_OK;
}