{
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