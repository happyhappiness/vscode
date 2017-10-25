int
UrgSSLConnect (struct UrlData *data)
{
#ifdef USE_SSLEAY
    int err;
    char * str;
    SSL_METHOD *req_method;

    /* mark this is being ssl enabled from here on out. */
    data->use_ssl = 1;

    /* Lets get nice error messages */
    SSL_load_error_strings();

#ifdef HAVE_RAND_STATUS
    /* RAND_status() was introduced in OpenSSL 0.9.5 */
    if(0 == RAND_status())
#endif
    {
      /* We need to seed the PRNG properly! */
#ifdef HAVE_RAND_SCREEN
      /* This one gets a random value by reading the currently shown screen */
      RAND_screen();
#else
      int len;
      char *area = MakeFormBoundary();
      if(!area)
	return 3; /* out of memory */
	
      len = strlen(area);

      RAND_seed(area, len);

      free(area); /* now remove the random junk */
#endif
    }
    
    /* Setup all the global SSL stuff */
    SSLeay_add_ssl_algorithms();

    switch(data->ssl_version) {
    default:
      req_method = SSLv23_client_method();
      break;
    case 2:
      req_method = SSLv2_client_method();
      break;
    case 3:
      req_method = SSLv3_client_method();
      break;
    }
    
    data->ctx = SSL_CTX_new(req_method);

    if(!data->ctx) {
      failf(data, "SSL: couldn't create a context!");
      return 1;
    }
    
    if(data->cert) {
      if (!SSL_cert_stuff(data, data->cert, data->cert)) {
	failf(data, "couldn't use certificate!\n");
	return 2;
      }
    }

#if SSL_VERIFY_CERT
    SSL_CTX_set_verify(data->ctx,
                       SSL_VERIFY_PEER|SSL_VERIFY_FAIL_IF_NO_PEER_CERT|
                       SSL_VERIFY_CLIENT_ONCE,
                       cert_verify_callback);
#endif

    /* Lets make an SSL structure */
    data->ssl = SSL_new (data->ctx);
    SSL_set_connect_state (data->ssl);

    data->server_cert = 0x0;

    /* pass the raw socket into the SSL layers */
    SSL_set_fd (data->ssl, data->firstsocket);
    err = SSL_connect (data->ssl);

    if (-1 == err) {
      err = ERR_get_error(); 
      failf(data, "SSL: %s", ERR_error_string(err, NULL));
      return 10;
    }


    infof (data, "SSL connection using %s\n", SSL_get_cipher (data->ssl));
  
    /* Get server's certificate (note: beware of dynamic allocation) - opt */
    /* major serious hack alert -- we should check certificates
     * to authenticate the server; otherwise we risk man-in-the-middle
     * attack
     */

    data->server_cert = SSL_get_peer_certificate (data->ssl);
    if(!data->server_cert) {
      failf(data, "SSL: couldn't get peer certificate!");
      return 3;
    }
    infof (data, "Server certificate:\n");
  
    str = X509_NAME_oneline (X509_get_subject_name (data->server_cert), NULL, 0);
    if(!str) {
      failf(data, "SSL: couldn't get X509-subject!");
      return 4;
    }
    infof (data, "\t subject: %s\n", str);
    Free (str);

    str = X509_NAME_oneline (X509_get_issuer_name  (data->server_cert), NULL, 0);
    if(!str) {
      failf(data, "SSL: couldn't get X509-issuer name!");
      return 5;
    }
    infof (data, "\t issuer: %s\n", str);
    Free (str);

    /* We could do all sorts of certificate verification stuff here before
       deallocating the certificate. */


#if SSL_VERIFY_CERT
    infof(data, "Verify result: %d\n", SSL_get_verify_result(data->ssl));
#endif



    X509_free (data->server_cert);
#else /* USE_SSLEAY */
    /* this is for "-ansi -Wall -pedantic" to stop complaining!   (rabe) */
    (void) data;
#endif
    return 0;
}