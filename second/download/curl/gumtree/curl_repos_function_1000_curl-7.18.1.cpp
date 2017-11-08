static CURLcode Curl_ldap(struct connectdata *conn, bool *done)
{
  CURLcode status = CURLE_OK;
  int rc = 0;
  LDAP *server = NULL;
  LDAPURLDesc *ludp = NULL;
  LDAPMessage *result = NULL;
  LDAPMessage *entryIterator;
  int num = 0;
  struct SessionHandle *data=conn->data;
  int ldap_proto = LDAP_VERSION3;
  int ldap_ssl = 0;
  char *val_b64;
  size_t val_b64_sz;
#ifdef LDAP_OPT_NETWORK_TIMEOUT
  struct timeval ldap_timeout = {10,0}; /* 10 sec connection/search timeout */
#endif

  *done = TRUE; /* unconditionally */
  infof(data, "LDAP local: LDAP Vendor = %s ; LDAP Version = %d\n",
          LDAP_VENDOR_NAME, LDAP_VENDOR_VERSION);
  infof(data, "LDAP local: %s\n", data->change.url);

#ifdef HAVE_LDAP_URL_PARSE
  rc = ldap_url_parse(data->change.url, &ludp);
#else
  rc = _ldap_url_parse(conn, &ludp);
#endif
  if(rc != 0) {
    failf(data, "LDAP local: %s", ldap_err2string(rc));
    status = CURLE_LDAP_INVALID_URL;
    goto quit;
  }

  /* Get the URL scheme ( either ldap or ldaps ) */
  if(strequal(conn->protostr, "LDAPS"))
    ldap_ssl = 1;
  infof(data, "LDAP local: trying to establish %s connection\n",
          ldap_ssl ? "encrypted" : "cleartext");

#ifdef LDAP_OPT_NETWORK_TIMEOUT
  ldap_set_option(NULL, LDAP_OPT_NETWORK_TIMEOUT, &ldap_timeout);
#endif
  ldap_set_option(NULL, LDAP_OPT_PROTOCOL_VERSION, &ldap_proto);

  if(ldap_ssl) {
#ifdef HAVE_LDAP_SSL
#ifdef CURL_LDAP_WIN
    /* Win32 LDAP SDK doesnt support insecure mode without CA! */
    server = ldap_sslinit(conn->host.name, (int)conn->port, 1);
    ldap_set_option(server, LDAP_OPT_SSL, LDAP_OPT_ON);
#else
    int ldap_option;
    char* ldap_ca = data->set.str[STRING_SSL_CAFILE];
#if defined(CURL_HAS_NOVELL_LDAPSDK)
    rc = ldapssl_client_init(NULL, NULL);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ldapssl_client_init %s", ldap_err2string(rc));
      status = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
    if(data->set.ssl.verifypeer) {
      /* Novell SDK supports DER or BASE64 files. */
      int cert_type = LDAPSSL_CERT_FILETYPE_B64;
      if((data->set.str[STRING_CERT_TYPE]) &&
              (strequal(data->set.str[STRING_CERT_TYPE], "DER")))
        cert_type = LDAPSSL_CERT_FILETYPE_DER;
      if(!ldap_ca) {
        failf(data, "LDAP local: ERROR %s CA cert not set!",
              (cert_type == LDAPSSL_CERT_FILETYPE_DER ? "DER" : "PEM"));
        status = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      infof(data, "LDAP local: using %s CA cert '%s'\n",
              (cert_type == LDAPSSL_CERT_FILETYPE_DER ? "DER" : "PEM"),
              ldap_ca);
      rc = ldapssl_add_trusted_cert(ldap_ca, cert_type);
      if(rc != LDAP_SUCCESS) {
        failf(data, "LDAP local: ERROR setting %s CA cert: %s",
                (cert_type == LDAPSSL_CERT_FILETYPE_DER ? "DER" : "PEM"),
                ldap_err2string(rc));
        status = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      ldap_option = LDAPSSL_VERIFY_SERVER;
    } else {
      ldap_option = LDAPSSL_VERIFY_NONE;
    }
    rc = ldapssl_set_verify_mode(ldap_option);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR setting cert verify mode: %s",
              ldap_err2string(rc));
      status = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
    server = ldapssl_init(conn->host.name, (int)conn->port, 1);
    if(server == NULL) {
      failf(data, "LDAP local: Cannot connect to %s:%d",
              conn->host.name, conn->port);
      status = CURLE_COULDNT_CONNECT;
      goto quit;
    }
#elif defined(LDAP_OPT_X_TLS)
    if(data->set.ssl.verifypeer) {
      /* OpenLDAP SDK supports BASE64 files. */
      if((data->set.str[STRING_CERT_TYPE]) &&
              (!strequal(data->set.str[STRING_CERT_TYPE], "PEM"))) {
        failf(data, "LDAP local: ERROR OpenLDAP does only support PEM cert-type!");
        status = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      if(!ldap_ca) {
        failf(data, "LDAP local: ERROR PEM CA cert not set!");
        status = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      infof(data, "LDAP local: using PEM CA cert: %s\n", ldap_ca);
      rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_CACERTFILE, ldap_ca);
      if(rc != LDAP_SUCCESS) {
        failf(data, "LDAP local: ERROR setting PEM CA cert: %s",
                ldap_err2string(rc));
        status = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      ldap_option = LDAP_OPT_X_TLS_DEMAND;
    } else {
      ldap_option = LDAP_OPT_X_TLS_NEVER;
    }
    rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_REQUIRE_CERT, &ldap_option);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR setting cert verify mode: %s",
              ldap_err2string(rc));
      status = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
    server = ldap_init(conn->host.name, (int)conn->port);
    if(server == NULL) {
      failf(data, "LDAP local: Cannot connect to %s:%d",
              conn->host.name, conn->port);
      status = CURLE_COULDNT_CONNECT;
      goto quit;
    }
    ldap_option = LDAP_OPT_X_TLS_HARD;
    rc = ldap_set_option(server, LDAP_OPT_X_TLS, &ldap_option);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR setting SSL/TLS mode: %s",
              ldap_err2string(rc));
      status = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
/*
    rc = ldap_start_tls_s(server, NULL, NULL);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR starting SSL/TLS mode: %s",
              ldap_err2string(rc));
      status = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
*/
#else
    /* we should probably never come up to here since configure
       should check in first place if we can support LDAP SSL/TLS */
    failf(data, "LDAP local: SSL/TLS not supported with this version "
            "of the OpenLDAP toolkit\n");
    status = CURLE_SSL_CERTPROBLEM;
    goto quit;
#endif
#endif
#endif /* CURL_LDAP_USE_SSL */
  } else {
    server = ldap_init(conn->host.name, (int)conn->port);
    if(server == NULL) {
      failf(data, "LDAP local: Cannot connect to %s:%d",
              conn->host.name, conn->port);
      status = CURLE_COULDNT_CONNECT;
      goto quit;
    }
  }
#ifdef CURL_LDAP_WIN
  ldap_set_option(server, LDAP_OPT_PROTOCOL_VERSION, &ldap_proto);
#endif

  rc = ldap_simple_bind_s(server,
                          conn->bits.user_passwd ? conn->user : NULL,
                          conn->bits.user_passwd ? conn->passwd : NULL);
  if(!ldap_ssl && rc != 0) {
    ldap_proto = LDAP_VERSION2;
    ldap_set_option(server, LDAP_OPT_PROTOCOL_VERSION, &ldap_proto);
    rc = ldap_simple_bind_s(server,
                            conn->bits.user_passwd ? conn->user : NULL,
                            conn->bits.user_passwd ? conn->passwd : NULL);
  }
  if(rc != 0) {
     failf(data, "LDAP local: ldap_simple_bind_s %s", ldap_err2string(rc));
     status = CURLE_LDAP_CANNOT_BIND;
     goto quit;
  }

  rc = ldap_search_s(server, ludp->lud_dn, ludp->lud_scope,
                     ludp->lud_filter, ludp->lud_attrs, 0, &result);

  if(rc != 0 && rc != LDAP_SIZELIMIT_EXCEEDED) {
    failf(data, "LDAP remote: %s", ldap_err2string(rc));
    status = CURLE_LDAP_SEARCH_FAILED;
    goto quit;
  }

  for(num = 0, entryIterator = ldap_first_entry(server, result);
      entryIterator;
      entryIterator = ldap_next_entry(server, entryIterator), num++)
  {
    BerElement *ber = NULL;
    char  *attribute;       /*! suspicious that this isn't 'const' */
    char  *dn = ldap_get_dn(server, entryIterator);
    int i;

    Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"DN: ", 4);
    Curl_client_write(conn, CLIENTWRITE_BODY, (char *)dn, 0);
    Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 1);

    for (attribute = ldap_first_attribute(server, entryIterator, &ber);
         attribute;
         attribute = ldap_next_attribute(server, entryIterator, ber))
    {
      BerValue **vals = ldap_get_values_len(server, entryIterator, attribute);

      if(vals != NULL)
      {
        for (i = 0; (vals[i] != NULL); i++)
        {
          Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\t", 1);
          Curl_client_write(conn, CLIENTWRITE_BODY, (char *) attribute, 0);
          Curl_client_write(conn, CLIENTWRITE_BODY, (char *)": ", 2);
          if((strlen(attribute) > 7) &&
              (strcmp(";binary",
                      (char *)attribute +
                      (strlen((char *)attribute) - 7)) == 0)) {
            /* Binary attribute, encode to base64. */
            val_b64_sz = Curl_base64_encode(conn->data,
                                            vals[i]->bv_val,
                                            vals[i]->bv_len,
                                            &val_b64);
            if(val_b64_sz > 0) {
              Curl_client_write(conn, CLIENTWRITE_BODY, val_b64, val_b64_sz);
              free(val_b64);
            }
          } else
            Curl_client_write(conn, CLIENTWRITE_BODY, vals[i]->bv_val,
                              vals[i]->bv_len);
          Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 0);
        }

        /* Free memory used to store values */
        ldap_value_free_len(vals);
      }
      Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 1);

      ldap_memfree(attribute);
    }
    ldap_memfree(dn);
    if(ber)
       ber_free(ber, 0);
  }

quit:
  if(result) {
    ldap_msgfree(result);
    LDAP_TRACE (("Received %d entries\n", num));
  }
  if(rc == LDAP_SIZELIMIT_EXCEEDED)
    infof(data, "There are more than %d entries\n", num);
  if(ludp)
    ldap_free_urldesc(ludp);
  if(server)
    ldap_unbind_s(server);
#if defined(HAVE_LDAP_SSL) && defined(CURL_HAS_NOVELL_LDAPSDK)
  if(ldap_ssl)
    ldapssl_client_deinit();
#endif /* HAVE_LDAP_SSL && CURL_HAS_NOVELL_LDAPSDK */

  /* no data to transfer */
  Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
  conn->bits.close = TRUE;

  return status;
}