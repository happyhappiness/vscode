static CURLcode Curl_ldap(struct connectdata *conn, bool *done)
{
  CURLcode result = CURLE_OK;
  int rc = 0;
  LDAP *server = NULL;
  LDAPURLDesc *ludp = NULL;
  LDAPMessage *ldapmsg = NULL;
  LDAPMessage *entryIterator;
  int num = 0;
  struct Curl_easy *data = conn->data;
  int ldap_proto = LDAP_VERSION3;
  int ldap_ssl = 0;
  char *val_b64 = NULL;
  size_t val_b64_sz = 0;
  curl_off_t dlsize = 0;
#ifdef LDAP_OPT_NETWORK_TIMEOUT
  struct timeval ldap_timeout = {10, 0}; /* 10 sec connection/search timeout */
#endif
#if defined(USE_WIN32_LDAP)
  TCHAR *host = NULL;
#else
  char *host = NULL;
#endif
  char *user = NULL;
  char *passwd = NULL;

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
    result = CURLE_LDAP_INVALID_URL;
    goto quit;
  }

  /* Get the URL scheme (either ldap or ldaps) */
  if(conn->given->flags & PROTOPT_SSL)
    ldap_ssl = 1;
  infof(data, "LDAP local: trying to establish %s connection\n",
          ldap_ssl ? "encrypted" : "cleartext");

#if defined(USE_WIN32_LDAP)
  host = Curl_convert_UTF8_to_tchar(conn->host.name);
  if(!host) {
    result = CURLE_OUT_OF_MEMORY;

    goto quit;
  }
#else
  host = conn->host.name;
#endif

  if(conn->bits.user_passwd) {
    user = conn->user;
    passwd = conn->passwd;
  }

#ifdef LDAP_OPT_NETWORK_TIMEOUT
  ldap_set_option(NULL, LDAP_OPT_NETWORK_TIMEOUT, &ldap_timeout);
#endif
  ldap_set_option(NULL, LDAP_OPT_PROTOCOL_VERSION, &ldap_proto);

  if(ldap_ssl) {
#ifdef HAVE_LDAP_SSL
#ifdef USE_WIN32_LDAP
    /* Win32 LDAP SDK doesn't support insecure mode without CA! */
    server = ldap_sslinit(host, (int)conn->port, 1);
    ldap_set_option(server, LDAP_OPT_SSL, LDAP_OPT_ON);
#else
    int ldap_option;
    char *ldap_ca = conn->ssl_config.CAfile;
#if defined(CURL_HAS_NOVELL_LDAPSDK)
    rc = ldapssl_client_init(NULL, NULL);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ldapssl_client_init %s", ldap_err2string(rc));
      result = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
    if(conn->ssl_config.verifypeer) {
      /* Novell SDK supports DER or BASE64 files. */
      int cert_type = LDAPSSL_CERT_FILETYPE_B64;
      if((data->set.ssl.cert_type) &&
         (strcasecompare(data->set.ssl.cert_type, "DER")))
        cert_type = LDAPSSL_CERT_FILETYPE_DER;
      if(!ldap_ca) {
        failf(data, "LDAP local: ERROR %s CA cert not set!",
              (cert_type == LDAPSSL_CERT_FILETYPE_DER ? "DER" : "PEM"));
        result = CURLE_SSL_CERTPROBLEM;
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
        result = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      ldap_option = LDAPSSL_VERIFY_SERVER;
    }
    else
      ldap_option = LDAPSSL_VERIFY_NONE;
    rc = ldapssl_set_verify_mode(ldap_option);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR setting cert verify mode: %s",
              ldap_err2string(rc));
      result = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
    server = ldapssl_init(host, (int)conn->port, 1);
    if(server == NULL) {
      failf(data, "LDAP local: Cannot connect to %s:%ld",
            conn->host.dispname, conn->port);
      result = CURLE_COULDNT_CONNECT;
      goto quit;
    }
#elif defined(LDAP_OPT_X_TLS)
    if(conn->ssl_config.verifypeer) {
      /* OpenLDAP SDK supports BASE64 files. */
      if((data->set.ssl.cert_type) &&
         (!strcasecompare(data->set.ssl.cert_type, "PEM"))) {
        failf(data, "LDAP local: ERROR OpenLDAP only supports PEM cert-type!");
        result = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      if(!ldap_ca) {
        failf(data, "LDAP local: ERROR PEM CA cert not set!");
        result = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      infof(data, "LDAP local: using PEM CA cert: %s\n", ldap_ca);
      rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_CACERTFILE, ldap_ca);
      if(rc != LDAP_SUCCESS) {
        failf(data, "LDAP local: ERROR setting PEM CA cert: %s",
                ldap_err2string(rc));
        result = CURLE_SSL_CERTPROBLEM;
        goto quit;
      }
      ldap_option = LDAP_OPT_X_TLS_DEMAND;
    }
    else
      ldap_option = LDAP_OPT_X_TLS_NEVER;

    rc = ldap_set_option(NULL, LDAP_OPT_X_TLS_REQUIRE_CERT, &ldap_option);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR setting cert verify mode: %s",
              ldap_err2string(rc));
      result = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
    server = ldap_init(host, (int)conn->port);
    if(server == NULL) {
      failf(data, "LDAP local: Cannot connect to %s:%ld",
            conn->host.dispname, conn->port);
      result = CURLE_COULDNT_CONNECT;
      goto quit;
    }
    ldap_option = LDAP_OPT_X_TLS_HARD;
    rc = ldap_set_option(server, LDAP_OPT_X_TLS, &ldap_option);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR setting SSL/TLS mode: %s",
              ldap_err2string(rc));
      result = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
/*
    rc = ldap_start_tls_s(server, NULL, NULL);
    if(rc != LDAP_SUCCESS) {
      failf(data, "LDAP local: ERROR starting SSL/TLS mode: %s",
              ldap_err2string(rc));
      result = CURLE_SSL_CERTPROBLEM;
      goto quit;
    }
*/
#else
    /* we should probably never come up to here since configure
       should check in first place if we can support LDAP SSL/TLS */
    failf(data, "LDAP local: SSL/TLS not supported with this version "
            "of the OpenLDAP toolkit\n");
    result = CURLE_SSL_CERTPROBLEM;
    goto quit;
#endif
#endif
#endif /* CURL_LDAP_USE_SSL */
  }
  else {
    server = ldap_init(host, (int)conn->port);
    if(server == NULL) {
      failf(data, "LDAP local: Cannot connect to %s:%ld",
            conn->host.dispname, conn->port);
      result = CURLE_COULDNT_CONNECT;
      goto quit;
    }
  }
#ifdef USE_WIN32_LDAP
  ldap_set_option(server, LDAP_OPT_PROTOCOL_VERSION, &ldap_proto);
#endif

#ifdef USE_WIN32_LDAP
  rc = ldap_win_bind(conn, server, user, passwd);
#else
  rc = ldap_simple_bind_s(server, user, passwd);
#endif
  if(!ldap_ssl && rc != 0) {
    ldap_proto = LDAP_VERSION2;
    ldap_set_option(server, LDAP_OPT_PROTOCOL_VERSION, &ldap_proto);
#ifdef USE_WIN32_LDAP
    rc = ldap_win_bind(conn, server, user, passwd);
#else
    rc = ldap_simple_bind_s(server, user, passwd);
#endif
  }
  if(rc != 0) {
    failf(data, "LDAP local: ldap_simple_bind_s %s", ldap_err2string(rc));
    result = CURLE_LDAP_CANNOT_BIND;
    goto quit;
  }

  rc = ldap_search_s(server, ludp->lud_dn, ludp->lud_scope,
                     ludp->lud_filter, ludp->lud_attrs, 0, &ldapmsg);

  if(rc != 0 && rc != LDAP_SIZELIMIT_EXCEEDED) {
    failf(data, "LDAP remote: %s", ldap_err2string(rc));
    result = CURLE_LDAP_SEARCH_FAILED;
    goto quit;
  }

  for(num = 0, entryIterator = ldap_first_entry(server, ldapmsg);
      entryIterator;
      entryIterator = ldap_next_entry(server, entryIterator), num++) {
    BerElement *ber = NULL;
#if defined(USE_WIN32_LDAP)
    TCHAR *attribute;
#else
    char  *attribute;       /*! suspicious that this isn't 'const' */
#endif
    int i;

    /* Get the DN and write it to the client */
    {
      char *name;
      size_t name_len;
#if defined(USE_WIN32_LDAP)
      TCHAR *dn = ldap_get_dn(server, entryIterator);
      name = Curl_convert_tchar_to_UTF8(dn);
      if(!name) {
        ldap_memfree(dn);

        result = CURLE_OUT_OF_MEMORY;

        goto quit;
      }
#else
      char *dn = name = ldap_get_dn(server, entryIterator);
#endif
      name_len = strlen(name);

      result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"DN: ", 4);
      if(result) {
#if defined(USE_WIN32_LDAP)
        Curl_unicodefree(name);
#endif
        ldap_memfree(dn);

        goto quit;
      }

      result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *) name,
                                 name_len);
      if(result) {
#if defined(USE_WIN32_LDAP)
        Curl_unicodefree(name);
#endif
        ldap_memfree(dn);

        goto quit;
      }

      result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 1);
      if(result) {
#if defined(USE_WIN32_LDAP)
        Curl_unicodefree(name);
#endif
        ldap_memfree(dn);

        goto quit;
      }

      dlsize += name_len + 5;

#if defined(USE_WIN32_LDAP)
      Curl_unicodefree(name);
#endif
      ldap_memfree(dn);
    }

    /* Get the attributes and write them to the client */
    for(attribute = ldap_first_attribute(server, entryIterator, &ber);
        attribute;
        attribute = ldap_next_attribute(server, entryIterator, ber)) {
      BerValue **vals;
      size_t attr_len;
#if defined(USE_WIN32_LDAP)
      char *attr = Curl_convert_tchar_to_UTF8(attribute);
      if(!attr) {
        if(ber)
          ber_free(ber, 0);

        result = CURLE_OUT_OF_MEMORY;

        goto quit;
    }
#else
      char *attr = attribute;
#endif
      attr_len = strlen(attr);

      vals = ldap_get_values_len(server, entryIterator, attribute);
      if(vals != NULL) {
        for(i = 0; (vals[i] != NULL); i++) {
          result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\t", 1);
          if(result) {
            ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
            Curl_unicodefree(attr);
#endif
            ldap_memfree(attribute);
            if(ber)
              ber_free(ber, 0);

            goto quit;
          }

          result = Curl_client_write(conn, CLIENTWRITE_BODY,
                                     (char *) attr, attr_len);
          if(result) {
            ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
            Curl_unicodefree(attr);
#endif
            ldap_memfree(attribute);
            if(ber)
              ber_free(ber, 0);

            goto quit;
          }

          result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)": ", 2);
          if(result) {
            ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
            Curl_unicodefree(attr);
#endif
            ldap_memfree(attribute);
            if(ber)
              ber_free(ber, 0);

            goto quit;
          }

          dlsize += attr_len + 3;

          if((attr_len > 7) &&
             (strcmp(";binary", (char *) attr + (attr_len - 7)) == 0)) {
            /* Binary attribute, encode to base64. */
            result = Curl_base64_encode(data,
                                        vals[i]->bv_val,
                                        vals[i]->bv_len,
                                        &val_b64,
                                        &val_b64_sz);
            if(result) {
              ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
              Curl_unicodefree(attr);
#endif
              ldap_memfree(attribute);
              if(ber)
                ber_free(ber, 0);

              goto quit;
            }

            if(val_b64_sz > 0) {
              result = Curl_client_write(conn, CLIENTWRITE_BODY, val_b64,
                                         val_b64_sz);
              free(val_b64);
              if(result) {
                ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
                Curl_unicodefree(attr);
#endif
                ldap_memfree(attribute);
                if(ber)
                  ber_free(ber, 0);

                goto quit;
              }

              dlsize += val_b64_sz;
            }
          }
          else {
            result = Curl_client_write(conn, CLIENTWRITE_BODY, vals[i]->bv_val,
                                       vals[i]->bv_len);
            if(result) {
              ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
              Curl_unicodefree(attr);
#endif
              ldap_memfree(attribute);
              if(ber)
                ber_free(ber, 0);

              goto quit;
            }

            dlsize += vals[i]->bv_len;
          }

          result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 1);
          if(result) {
            ldap_value_free_len(vals);
#if defined(USE_WIN32_LDAP)
            Curl_unicodefree(attr);
#endif
            ldap_memfree(attribute);
            if(ber)
              ber_free(ber, 0);

            goto quit;
          }

          dlsize++;
        }

        /* Free memory used to store values */
        ldap_value_free_len(vals);
      }

      /* Free the attribute as we are done with it */
#if defined(USE_WIN32_LDAP)
      Curl_unicodefree(attr);
#endif
      ldap_memfree(attribute);

      result = Curl_client_write(conn, CLIENTWRITE_BODY, (char *)"\n", 1);
      if(result)
        goto quit;
      dlsize++;
      Curl_pgrsSetDownloadCounter(data, dlsize);
    }

    if(ber)
       ber_free(ber, 0);
  }

quit:
  if(ldapmsg) {
    ldap_msgfree(ldapmsg);
    LDAP_TRACE(("Received %d entries\n", num));
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

#if defined(USE_WIN32_LDAP)
  Curl_unicodefree(host);
#endif

  /* no data to transfer */
  Curl_setup_transfer(conn, -1, -1, FALSE, NULL, -1, NULL);
  connclose(conn, "LDAP connection always disable re-use");

  return result;
}