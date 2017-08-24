{
    char *binddn;
    struct berval passwd;

    if(conn->bits.user_passwd) {
      binddn = conn->user;
      passwd.bv_val = conn->passwd;
      passwd.bv_len = strlen(passwd.bv_val);
    }
    else {
      binddn = NULL;
      passwd.bv_val = NULL;
      passwd.bv_len = 0;
    }
    rc = ldap_sasl_bind(li->ld, binddn, LDAP_SASL_SIMPLE, &passwd,
                        NULL, NULL, &li->msgid);
    if(rc)
      return CURLE_LDAP_CANNOT_BIND;
    li->didbind = TRUE;
    if(tvp)
      return CURLE_OK;
  }