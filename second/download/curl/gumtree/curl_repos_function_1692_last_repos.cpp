static CURLcode pop3_state_capa_resp(struct connectdata *conn, int pop3code,
                                     pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  const char *line = data->state.buffer;
  size_t len = strlen(line);
  size_t wordlen;

  (void)instate; /* no use for this yet */

  /* Do we have a untagged continuation response? */
  if(pop3code == '*') {
    /* Does the server support the STLS capability? */
    if(len >= 4 && !memcmp(line, "STLS", 4))
      pop3c->tls_supported = TRUE;

    /* Does the server support clear text authentication? */
    else if(len >= 4 && !memcmp(line, "USER", 4))
      pop3c->authtypes |= POP3_TYPE_CLEARTEXT;

    /* Does the server support SASL based authentication? */
    else if(len >= 5 && !memcmp(line, "SASL ", 5)) {
      pop3c->authtypes |= POP3_TYPE_SASL;

      /* Advance past the SASL keyword */
      line += 5;
      len -= 5;

      /* Loop through the data line */
      for(;;) {
        size_t llen;
        unsigned int mechbit;

        while(len &&
              (*line == ' ' || *line == '\t' ||
               *line == '\r' || *line == '\n')) {

          line++;
          len--;
        }

        if(!len)
          break;

        /* Extract the word */
        for(wordlen = 0; wordlen < len && line[wordlen] != ' ' &&
              line[wordlen] != '\t' && line[wordlen] != '\r' &&
              line[wordlen] != '\n';)
          wordlen++;

        /* Test the word for a matching authentication mechanism */
        mechbit = Curl_sasl_decode_mech(line, wordlen, &llen);
        if(mechbit && llen == wordlen)
          pop3c->sasl.authmechs |= mechbit;

        line += wordlen;
        len -= wordlen;
      }
    }
  }
  else if(pop3code == '+') {
    if(data->set.use_ssl && !conn->ssl[FIRSTSOCKET].use) {
      /* We don't have a SSL/TLS connection yet, but SSL is requested */
      if(pop3c->tls_supported)
        /* Switch to TLS connection now */
        result = pop3_perform_starttls(conn);
      else if(data->set.use_ssl == CURLUSESSL_TRY)
        /* Fallback and carry on with authentication */
        result = pop3_perform_authentication(conn);
      else {
        failf(data, "STLS not supported.");
        result = CURLE_USE_SSL_FAILED;
      }
    }
    else
      result = pop3_perform_authentication(conn);
  }
  else {
    /* Clear text is supported when CAPA isn't recognised */
    pop3c->authtypes |= POP3_TYPE_CLEARTEXT;

    result = pop3_perform_authentication(conn);
  }

  return result;
}