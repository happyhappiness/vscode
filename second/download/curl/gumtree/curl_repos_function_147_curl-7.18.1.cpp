int
Curl_SSL_Init_a(SSLInit * init)

{
  int rc;
  unsigned int i;
  SSLInit ia;

  if (!init || (!init->keyringFileName && !init->keyringPassword))
    return SSL_Init(init);

  memcpy((char *) &ia, (char *) init, sizeof ia);

  if (ia.keyringFileName) {
    i = strlen(ia.keyringFileName);

    if (!(ia.keyringFileName = malloc(i + 1))) {
      errno = ENOMEM;
      return SSL_ERROR_IO;
      }

    QadrtConvertA2E(ia.keyringFileName, init->keyringFileName, i, i);
    ia.keyringFileName[i] = '\0';
    }

  if (ia.keyringPassword) {
    i = strlen(ia.keyringPassword);

    if (!(ia.keyringPassword = malloc(i + 1))) {
      if (ia.keyringFileName)
        free(ia.keyringFileName);

      errno = ENOMEM;
      return SSL_ERROR_IO;
      }

    QadrtConvertA2E(ia.keyringPassword, init->keyringPassword, i, i);
    ia.keyringPassword[i] = '\0';
    }

  rc = SSL_Init(&ia);

  if (ia.keyringFileName)
    free(ia.keyringFileName);

  if (ia.keyringPassword)
    free(ia.keyringPassword);

  return rc;
}