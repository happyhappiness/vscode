CURLcode
Curl_gtls_connect(struct connectdata *conn,
                  int sockindex)

{
  const int cert_type_priority[] = { GNUTLS_CRT_X509, 0 };
  struct SessionHandle *data = conn->data;
  gnutls_session session;
  int rc;
  unsigned int cert_list_size;
  const gnutls_datum *chainp;
  unsigned int verify_status;
  gnutls_x509_crt x509_cert;
  char certbuf[256]; /* big enough? */
  size_t size;
  unsigned int algo;
  unsigned int bits;
  time_t clock;
  const char *ptr;
  void *ssl_sessionid;
  size_t ssl_idsize;

  /* GnuTLS only supports TLSv1 (and SSLv3?) */
  if(data->set.ssl.version == CURL_SSLVERSION_SSLv2) {
    failf(data, "GnuTLS does not support SSLv2");
    return CURLE_SSL_CONNECT_ERROR;
  }

  /* allocate a cred struct */
  rc = gnutls_certificate_allocate_credentials(&conn->ssl[sockindex].cred);
  if(rc < 0) {
    failf(data, "gnutls_cert_all_cred() failed: %s", gnutls_strerror(rc));
    return CURLE_SSL_CONNECT_ERROR;
  }

  if(data->set.ssl.CAfile) {
    /* set the trusted CA cert bundle file */
    gnutls_certificate_set_verify_flags(conn->ssl[sockindex].cred,
                                        GNUTLS_VERIFY_ALLOW_X509_V1_CA_CRT);

    rc = gnutls_certificate_set_x509_trust_file(conn->ssl[sockindex].cred,
                                                data->set.ssl.CAfile,
                                                GNUTLS_X509_FMT_PEM);
    if(rc < 0)
      infof(data, "error reading ca cert file %s (%s)\n",
            data->set.ssl.CAfile, gnutls_strerror(rc));
    else
      infof(data, "found %d certificates in %s\n",
            rc, data->set.ssl.CAfile);
  }

  /* Initialize TLS session as a client */
  rc = gnutls_init(&conn->ssl[sockindex].session, GNUTLS_CLIENT);
  if(rc) {
    failf(data, "gnutls_init() failed: %d", rc);
    return CURLE_SSL_CONNECT_ERROR;
  }

  /* convenient assign */
  session = conn->ssl[sockindex].session;

  /* Use default priorities */
  rc = gnutls_set_default_priority(session);
  if(rc < 0)
    return CURLE_SSL_CONNECT_ERROR;

  /* Sets the priority on the certificate types supported by gnutls. Priority
     is higher for types specified before others. After specifying the types
     you want, you must append a 0. */
  rc = gnutls_certificate_type_set_priority(session, cert_type_priority);
  if(rc < 0)
    return CURLE_SSL_CONNECT_ERROR;

  /* put the anonymous credentials to the current session */
  rc = gnutls_credentials_set(session, GNUTLS_CRD_CERTIFICATE,
                              conn->ssl[sockindex].cred);

  /* set the connection handle (file descriptor for the socket) */
  gnutls_transport_set_ptr(session,
                           (gnutls_transport_ptr)conn->sock[sockindex]);

  /* This might be a reconnect, so we check for a session ID in the cache
     to speed up things */

  if(!Curl_ssl_getsessionid(conn, &ssl_sessionid, &ssl_idsize)) {
    /* we got a session id, use it! */
    gnutls_session_set_data(session, ssl_sessionid, ssl_idsize);

    /* Informational message */
    infof (data, "SSL re-using session ID\n");
  }

  do {
    rc = gnutls_handshake(session);

    if((rc == GNUTLS_E_AGAIN) || (rc == GNUTLS_E_INTERRUPTED)) {
      long timeout_ms;
      long has_passed;

      if(data->set.timeout || data->set.connecttimeout) {
        /* get the most strict timeout of the ones converted to milliseconds */
        if(data->set.timeout &&
           (data->set.timeout>data->set.connecttimeout))
          timeout_ms = data->set.timeout*1000;
        else
          timeout_ms = data->set.connecttimeout*1000;
      }
      else
        timeout_ms = DEFAULT_CONNECT_TIMEOUT;

      /* Evaluate in milliseconds how much time that has passed */
      has_passed = Curl_tvdiff(Curl_tvnow(), data->progress.t_startsingle);

      /* subtract the passed time */
      timeout_ms -= has_passed;

      if(timeout_ms < 0) {
        /* a precaution, no need to continue if time already is up */
        failf(data, "SSL connection timeout");
        return CURLE_OPERATION_TIMEOUTED;
      }

      rc = Curl_select(conn->sock[sockindex],
                         conn->sock[sockindex], (int)timeout_ms);
      if(rc > 0)
        /* reabable or writable, go loop*/
        continue;
      else if(0 == rc) {
        /* timeout */
        failf(data, "SSL connection timeout");
        return CURLE_OPERATION_TIMEDOUT;
      }
      else {
        /* anything that gets here is fatally bad */
        failf(data, "select on SSL socket, errno: %d", Curl_ourerrno());
        return CURLE_SSL_CONNECT_ERROR;
      }
    }
    else
      break;
  } while(1);

  if (rc < 0) {
    failf(data, "gnutls_handshake() failed: %d", rc);
    /* gnutls_perror(ret); */
    return CURLE_SSL_CONNECT_ERROR;
  }

  /* This function will return the peer's raw certificate (chain) as sent by
     the peer. These certificates are in raw format (DER encoded for
     X.509). In case of a X.509 then a certificate list may be present. The
     first certificate in the list is the peer's certificate, following the
     issuer's certificate, then the issuer's issuer etc. */

  chainp = gnutls_certificate_get_peers(session, &cert_list_size);
  if(!chainp) {
    if(data->set.ssl.verifyhost) {
      failf(data, "failed to get server cert");
      return CURLE_SSL_PEER_CERTIFICATE;
    }
    infof(data, "\t common name: WARNING couldn't obtain\n");
  }

  /* This function will try to verify the peer's certificate and return its
     status (trusted, invalid etc.). The value of status should be one or more
     of the gnutls_certificate_status_t enumerated elements bitwise or'd. To
     avoid denial of service attacks some default upper limits regarding the
     certificate key size and chain size are set. To override them use
     gnutls_certificate_set_verify_limits(). */

  rc = gnutls_certificate_verify_peers2(session, &verify_status);
  if (rc < 0) {
    failf(data, "server cert verify failed: %d", rc);
    return CURLE_SSL_CONNECT_ERROR;
  }

  /* verify_status is a bitmask of gnutls_certificate_status bits */
  if(verify_status & GNUTLS_CERT_INVALID) {
    if (data->set.ssl.verifypeer) {
      failf(data, "server certificate verification failed. CAfile: %s",
            data->set.ssl.CAfile?data->set.ssl.CAfile:"none");
      return CURLE_SSL_CACERT;
    }
    else
      infof(data, "\t server certificate verification FAILED\n");
  }
  else
      infof(data, "\t server certificate verification OK\n");

  /* initialize an X.509 certificate structure. */
  gnutls_x509_crt_init(&x509_cert);

  /* convert the given DER or PEM encoded Certificate to the native
     gnutls_x509_crt_t format */
  gnutls_x509_crt_import(x509_cert, chainp, GNUTLS_X509_FMT_DER);

  size=sizeof(certbuf);
  rc = gnutls_x509_crt_get_dn_by_oid(x509_cert, GNUTLS_OID_X520_COMMON_NAME,
                                     0, /* the first and only one */
                                     FALSE,
                                     certbuf,
                                     &size);
  if(rc) {
    infof(data, "error fetching CN from cert:%s\n",
          gnutls_strerror(rc));
  }

  /* This function will check if the given certificate's subject matches the
     given hostname. This is a basic implementation of the matching described
     in RFC2818 (HTTPS), which takes into account wildcards, and the subject
     alternative name PKIX extension. Returns non zero on success, and zero on
     failure. */
  rc = gnutls_x509_crt_check_hostname(x509_cert, conn->host.name);

  if(!rc) {
    if (data->set.ssl.verifyhost > 1) {
      failf(data, "SSL: certificate subject name (%s) does not match "
            "target host name '%s'", certbuf, conn->host.dispname);
      gnutls_x509_crt_deinit(x509_cert);
      return CURLE_SSL_PEER_CERTIFICATE;
    }
    else
      infof(data, "\t common name: %s (does not match '%s')\n",
            certbuf, conn->host.dispname);
  }
  else
    infof(data, "\t common name: %s (matched)\n", certbuf);

  /* Show:

  - ciphers used
  - subject
  - start date
  - expire date
  - common name
  - issuer

  */

  /* public key algorithm's parameters */
  algo = gnutls_x509_crt_get_pk_algorithm(x509_cert, &bits);
  infof(data, "\t certificate public key: %s\n",
        gnutls_pk_algorithm_get_name(algo));

  /* version of the X.509 certificate. */
  infof(data, "\t certificate version: #%d\n",
        gnutls_x509_crt_get_version(x509_cert));


  size = sizeof(certbuf);
  gnutls_x509_crt_get_dn(x509_cert, certbuf, &size);
  infof(data, "\t subject: %s\n", certbuf);

  clock = gnutls_x509_crt_get_activation_time(x509_cert);
  showtime(data, "start date", clock);

  clock = gnutls_x509_crt_get_expiration_time(x509_cert);
  showtime(data, "expire date", clock);

  size = sizeof(certbuf);
  gnutls_x509_crt_get_issuer_dn(x509_cert, certbuf, &size);
  infof(data, "\t issuer: %s\n", certbuf);

  gnutls_x509_crt_deinit(x509_cert);

  /* compression algorithm (if any) */
  ptr = gnutls_compression_get_name(gnutls_compression_get(session));
  /* the *_get_name() says "NULL" if GNUTLS_COMP_NULL is returned */
  infof(data, "\t compression: %s\n", ptr);

  /* the name of the cipher used. ie 3DES. */
  ptr = gnutls_cipher_get_name(gnutls_cipher_get(session));
  infof(data, "\t cipher: %s\n", ptr);

  /* the MAC algorithms name. ie SHA1 */
  ptr = gnutls_mac_get_name(gnutls_mac_get(session));
  infof(data, "\t MAC: %s\n", ptr);

  if(!ssl_sessionid) {
    /* this session was not previously in the cache, add it now */

    /* get the session ID data size */
    gnutls_session_get_data(session, NULL, &ssl_idsize);
    ssl_sessionid = malloc(ssl_idsize); /* get a buffer for it */

    if(ssl_sessionid) {
      /* extract session ID to the allocated buffer */
      gnutls_session_get_data(session, ssl_sessionid, &ssl_idsize);

      /* store this session id */
      return Curl_ssl_addsessionid(conn, ssl_sessionid, ssl_idsize);
    }
  }

  return CURLE_OK;
}