{
  ldapconninfo *li;
  LDAPURLDesc *lud;
  struct Curl_easy *data=conn->data;
  int rc, proto;
  CURLcode status;

  rc = ldap_url_parse(data->change.url, &lud);
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
  proto = ldap_pvt_url_scheme2proto(lud->lud_scheme);
  ldap_free_urldesc(lud);

  li = calloc(1, sizeof(ldapconninfo));
  if(!li)
    return CURLE_OUT_OF_MEMORY;
  li->proto = proto;
  conn->proto.generic = li;
  connkeep(conn, "OpenLDAP default");
  /* TODO:
   * - provide option to choose SASL Binds instead of Simple
   */
  return CURLE_OK;
}