int
Curl_SSL_Init_Application_a(SSLInitApp * init_app)

{
  int rc;
  unsigned int i;
  SSLInitApp ia;

  if (!init_app || !init_app->applicationID || !init_app->applicationIDLen)
    return SSL_Init_Application(init_app);

  memcpy((char *) &ia, (char *) init_app, sizeof ia);
  i = ia.applicationIDLen;

  if (!(ia.applicationID = malloc(i + 1))) {
    errno = ENOMEM;
    return SSL_ERROR_IO;
    }

  QadrtConvertA2E(ia.applicationID, init_app->applicationID, i, i);
  ia.applicationID[i] = '\0';
  rc = SSL_Init_Application(&ia);
  free(ia.applicationID);
  init_app->localCertificateLen = ia.localCertificateLen;
  init_app->sessionType = ia.sessionType;
  return rc;
}