static CURLcode Curl_qsossl_init_session(struct SessionHandle * data)

{
  int rc;
  char * certname;
  SSLInit initstr;
  SSLInitApp initappstr;

  /* Initialize the job for SSL according to the current parameters.
   * QsoSSL offers two ways to do it: SSL_Init_Application() that uses an
   *  application identifier to select certificates in the main certificate
   *  store, and SSL_Init() that uses named keyring files and a password.
   * It is not possible to have different keyrings for the CAs and the
   *  local certificate. We thus use the certificate name to identify the
   *  keyring if given, else the CA file name.
   * If the key file name is given, it is taken as the password for the
   *  keyring in certificate file.
   * We first try to SSL_Init_Application(), then SSL_Init() if it failed.
   */

  certname = data->set.str[STRING_CERT];

  if(!certname) {
    certname = data->set.str[STRING_SSL_CAFILE];

    if(!certname)
      return CURLE_OK;          /* Use previous setup. */
    }

  memset((char *) &initappstr, 0, sizeof initappstr);
  initappstr.applicationID = certname;
  initappstr.applicationIDLen = strlen(certname);
  initappstr.protocol = TLSV1_SSLV3;
  initappstr.sessionType = SSL_REGISTERED_AS_CLIENT;
  rc = SSL_Init_Application(&initappstr);

  if(rc == SSL_ERROR_NOT_REGISTERED) {
    initstr.keyringFileName = certname;
    initstr.keyringPassword = data->set.str[STRING_KEY];
    initstr.cipherSuiteList = NULL;    /* Use default. */
    initstr.cipherSuiteListLen = 0;
    rc = SSL_Init(&initstr);
    }

  switch (rc) {

  case 0:                             /* No error. */
    break;

  case SSL_ERROR_IO:
    failf(data, "SSL_Init() I/O error: %s", strerror(errno));
    return CURLE_SSL_CONNECT_ERROR;

  case SSL_ERROR_BAD_CIPHER_SUITE:
    return CURLE_SSL_CIPHER;

  case SSL_ERROR_KEYPASSWORD_EXPIRED:
  case SSL_ERROR_NOT_REGISTERED:
    return CURLE_SSL_CONNECT_ERROR;

  case SSL_ERROR_NO_KEYRING:
    return CURLE_SSL_CACERT;

  case SSL_ERROR_CERT_EXPIRED:
    return CURLE_SSL_CERTPROBLEM;

  default:
    failf(data, "SSL_Init(): %s", SSL_Strerror(rc, NULL));
    return CURLE_SSL_CONNECT_ERROR;
  }

  return CURLE_OK;
}