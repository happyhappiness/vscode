static CURLcode set_ciphers(struct connectdata *conn,
                                        gsk_handle h, unsigned int *protoflags)
{
  struct Curl_easy *data = conn->data;
  const char *cipherlist = SSL_CONN_CONFIG(cipher_list);
  const char *clp;
  const gskit_cipher *ctp;
  int i;
  int l;
  bool unsupported;
  CURLcode result;
  struct {
    char *buf;
    char *ptr;
  } ciphers[CURL_GSKPROTO_LAST];

  /* Compile cipher list into GSKit-compatible cipher lists. */

  if(!cipherlist)
    return CURLE_OK;
  while(is_separator(*cipherlist))     /* Skip initial separators. */
    cipherlist++;
  if(!*cipherlist)
    return CURLE_OK;

  /* We allocate GSKit buffers of the same size as the input string: since
     GSKit tokens are always shorter than their cipher names, allocated buffers
     will always be large enough to accommodate the result. */
  l = strlen(cipherlist) + 1;
  memset((char *) ciphers, 0, sizeof ciphers);
  for(i = 0; i < CURL_GSKPROTO_LAST; i++) {
    ciphers[i].buf = malloc(l);
    if(!ciphers[i].buf) {
      while(i--)
        free(ciphers[i].buf);
      return CURLE_OUT_OF_MEMORY;
    }
    ciphers[i].ptr = ciphers[i].buf;
    *ciphers[i].ptr = '\0';
  }

  /* Process each cipher in input string. */
  unsupported = FALSE;
  result = CURLE_OK;
  for(;;) {
    for(clp = cipherlist; *cipherlist && !is_separator(*cipherlist);)
      cipherlist++;
    l = cipherlist - clp;
    if(!l)
      break;
    /* Search the cipher in our table. */
    for(ctp = ciphertable; ctp->name; ctp++)
      if(strncasecompare(ctp->name, clp, l) && !ctp->name[l])
        break;
    if(!ctp->name) {
      failf(data, "Unknown cipher %.*s", l, clp);
      result = CURLE_SSL_CIPHER;
    }
    else {
      unsupported |= !(ctp->versions & (CURL_GSKPROTO_SSLV2_MASK |
                        CURL_GSKPROTO_SSLV3_MASK | CURL_GSKPROTO_TLSV10_MASK));
      for(i = 0; i < CURL_GSKPROTO_LAST; i++) {
        if(ctp->versions & (1 << i)) {
          strcpy(ciphers[i].ptr, ctp->gsktoken);
          ciphers[i].ptr += strlen(ctp->gsktoken);
        }
      }
    }

   /* Advance to next cipher name or end of string. */
    while(is_separator(*cipherlist))
      cipherlist++;
  }

  /* Disable protocols with empty cipher lists. */
  for(i = 0; i < CURL_GSKPROTO_LAST; i++) {
    if(!(*protoflags & (1 << i)) || !ciphers[i].buf[0]) {
      *protoflags &= ~(1 << i);
      ciphers[i].buf[0] = '\0';
    }
  }

  /* Try to set-up TLSv1.1 and TLSv2.1 ciphers. */
  if(*protoflags & CURL_GSKPROTO_TLSV11_MASK) {
    result = set_buffer(data, h, GSK_TLSV11_CIPHER_SPECS,
                        ciphers[CURL_GSKPROTO_TLSV11].buf, TRUE);
    if(result == CURLE_UNSUPPORTED_PROTOCOL) {
      result = CURLE_OK;
      if(unsupported) {
        failf(data, "TLSv1.1-only ciphers are not yet supported");
        result = CURLE_SSL_CIPHER;
      }
    }
  }
  if(!result && (*protoflags & CURL_GSKPROTO_TLSV12_MASK)) {
    result = set_buffer(data, h, GSK_TLSV12_CIPHER_SPECS,
                        ciphers[CURL_GSKPROTO_TLSV12].buf, TRUE);
    if(result == CURLE_UNSUPPORTED_PROTOCOL) {
      result = CURLE_OK;
      if(unsupported) {
        failf(data, "TLSv1.2-only ciphers are not yet supported");
        result = CURLE_SSL_CIPHER;
      }
    }
  }

  /* Try to set-up TLSv1.0 ciphers. If not successful, concatenate them to
     the SSLv3 ciphers. OS/400 prior to version 7.1 will understand it. */
  if(!result && (*protoflags & CURL_GSKPROTO_TLSV10_MASK)) {
    result = set_buffer(data, h, GSK_TLSV10_CIPHER_SPECS,
                        ciphers[CURL_GSKPROTO_TLSV10].buf, TRUE);
    if(result == CURLE_UNSUPPORTED_PROTOCOL) {
      result = CURLE_OK;
      strcpy(ciphers[CURL_GSKPROTO_SSLV3].ptr,
             ciphers[CURL_GSKPROTO_TLSV10].ptr);
    }
  }

  /* Set-up other ciphers. */
  if(!result && (*protoflags & CURL_GSKPROTO_SSLV3_MASK))
    result = set_buffer(data, h, GSK_V3_CIPHER_SPECS,
                        ciphers[CURL_GSKPROTO_SSLV3].buf, FALSE);
  if(!result && (*protoflags & CURL_GSKPROTO_SSLV2_MASK))
    result = set_buffer(data, h, GSK_V2_CIPHER_SPECS,
                        ciphers[CURL_GSKPROTO_SSLV2].buf, FALSE);

  /* Clean-up. */
  for(i = 0; i < CURL_GSKPROTO_LAST; i++)
    free(ciphers[i].buf);

  return result;
}