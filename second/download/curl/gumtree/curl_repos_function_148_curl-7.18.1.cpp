char *
Curl_SSL_Strerror_a(int sslreturnvalue, SSLErrorMsg * serrmsgp)

{
  int i;
  char * cp;
  char * cp2;

  cp = SSL_Strerror(sslreturnvalue, serrmsgp);

  if (!cp)
    return cp;

  i = strlen(cp);

  if (!(cp2 = Curl_thread_buffer(LK_SSL_ERROR, MAX_CONV_EXPANSION * i + 1)))
    return cp2;

  i = QadrtConvertE2A(cp2, cp, MAX_CONV_EXPANSION * i, i);
  cp2[i] = '\0';
  return cp2;
}