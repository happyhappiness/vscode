static CURLcode pop3_parse_url_options(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
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
        pop3c->preftype = POP3_TYPE_NONE;
        pop3c->prefmech = SASL_AUTH_NONE;
      }

      while(*ptr && *ptr != ';') {
        ptr++;
        len++;
      }

      if(strnequal(value, "*", len)) {
        pop3c->preftype = POP3_TYPE_ANY;
        pop3c->prefmech = SASL_AUTH_ANY;
      }
      else if(strnequal(value, "+APOP", len)) {
        pop3c->preftype = POP3_TYPE_APOP;
        pop3c->prefmech = SASL_AUTH_NONE;
      }
      else if(strnequal(value, SASL_MECH_STRING_LOGIN, len)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech |= SASL_MECH_LOGIN;
      }
      else if(strnequal(value, SASL_MECH_STRING_PLAIN, len)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech |= SASL_MECH_PLAIN;
      }
      else if(strnequal(value, SASL_MECH_STRING_CRAM_MD5, len)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech |= SASL_MECH_CRAM_MD5;
      }
      else if(strnequal(value, SASL_MECH_STRING_DIGEST_MD5, len)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech |= SASL_MECH_DIGEST_MD5;
      }
      else if(strnequal(value, SASL_MECH_STRING_GSSAPI, len)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech |= SASL_MECH_GSSAPI;
      }
      else if(strnequal(value, SASL_MECH_STRING_NTLM, len)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech |= SASL_MECH_NTLM;
      }
      else if(strnequal(value, SASL_MECH_STRING_XOAUTH2, len)) {
        pop3c->preftype = POP3_TYPE_SASL;
        pop3c->prefmech |= SASL_MECH_XOAUTH2;
      }

      if(*ptr == ';')
        ptr++;
    }
    else
      result = CURLE_URL_MALFORMAT;
  }

  return result;
}