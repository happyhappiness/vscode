static CURLcode smtp_parse_url_options(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  const char *options = conn->options;
  const char *ptr = options;
  bool reset = TRUE;

  while(ptr && *ptr) {
    const char *key = ptr;

    while(*ptr && *ptr != '=')
        ptr++;

    if(strnequal(key, "AUTH", 4)) {
      size_t len = 0;
      const char *value = ++ptr;

      if(reset) {
        reset = FALSE;
        smtpc->prefmech = SASL_AUTH_NONE;
      }

      while(*ptr && *ptr != ';') {
        ptr++;
        len++;
      }

      if(strnequal(value, "*", len))
        smtpc->prefmech = SASL_AUTH_ANY;
      else if(strnequal(value, SASL_MECH_STRING_LOGIN, len))
        smtpc->prefmech |= SASL_MECH_LOGIN;
      else if(strnequal(value, SASL_MECH_STRING_PLAIN, len))
        smtpc->prefmech |= SASL_MECH_PLAIN;
      else if(strnequal(value, SASL_MECH_STRING_CRAM_MD5, len))
        smtpc->prefmech |= SASL_MECH_CRAM_MD5;
      else if(strnequal(value, SASL_MECH_STRING_DIGEST_MD5, len))
        smtpc->prefmech |= SASL_MECH_DIGEST_MD5;
      else if(strnequal(value, SASL_MECH_STRING_GSSAPI, len))
        smtpc->prefmech |= SASL_MECH_GSSAPI;
      else if(strnequal(value, SASL_MECH_STRING_NTLM, len))
        smtpc->prefmech |= SASL_MECH_NTLM;
      else if(strnequal(value, SASL_MECH_STRING_XOAUTH2, len))
        smtpc->prefmech |= SASL_MECH_XOAUTH2;

      if(*ptr == ';')
        ptr++;
    }
    else
      result = CURLE_URL_MALFORMAT;
  }

  return result;
}