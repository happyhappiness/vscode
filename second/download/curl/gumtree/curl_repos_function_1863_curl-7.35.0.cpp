static CURLcode smtp_state_ehlo_resp(struct connectdata *conn, int smtpcode,
                                     smtpstate instate)
{
  CURLcode result = CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct smtp_conn *smtpc = &conn->proto.smtpc;
  const char *line = data->state.buffer;
  size_t len = strlen(line);
  size_t wordlen;

  (void)instate; /* no use for this yet */

  if(smtpcode/100 != 2 && smtpcode != 1) {
    if((data->set.use_ssl <= CURLUSESSL_TRY || conn->ssl[FIRSTSOCKET].use) &&
     !conn->bits.user_passwd)
      result = smtp_perform_helo(conn);
    else {
      failf(data, "Remote access denied: %d", smtpcode);
      result = CURLE_REMOTE_ACCESS_DENIED;
    }
  }
  else {
    line += 4;
    len -= 4;

    /* Does the server support the STARTTLS capability? */
    if(len >= 8 && !memcmp(line, "STARTTLS", 8))
      smtpc->tls_supported = TRUE;

    /* Does the server support the SIZE capability? */
    else if(len >= 4 && !memcmp(line, "SIZE", 4))
      smtpc->size_supported = TRUE;

    /* Do we have the authentication mechanism list? */
    else if(len >= 5 && !memcmp(line, "AUTH ", 5)) {
      line += 5;
      len -= 5;

      /* Loop through the data line */
      for(;;) {
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
        if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_LOGIN))
          smtpc->authmechs |= SASL_MECH_LOGIN;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_PLAIN))
          smtpc->authmechs |= SASL_MECH_PLAIN;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_CRAM_MD5))
          smtpc->authmechs |= SASL_MECH_CRAM_MD5;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_DIGEST_MD5))
          smtpc->authmechs |= SASL_MECH_DIGEST_MD5;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_GSSAPI))
          smtpc->authmechs |= SASL_MECH_GSSAPI;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_EXTERNAL))
          smtpc->authmechs |= SASL_MECH_EXTERNAL;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_NTLM))
          smtpc->authmechs |= SASL_MECH_NTLM;
        else if(sasl_mech_equal(line, wordlen, SASL_MECH_STRING_XOAUTH2))
          smtpc->authmechs |= SASL_MECH_XOAUTH2;

        line += wordlen;
        len -= wordlen;
      }
    }

    if(smtpcode != 1) {
      if(data->set.use_ssl && !conn->ssl[FIRSTSOCKET].use) {
        /* We don't have a SSL/TLS connection yet, but SSL is requested */
        if(smtpc->tls_supported)
          /* Switch to TLS connection now */
          result = smtp_perform_starttls(conn);
        else if(data->set.use_ssl == CURLUSESSL_TRY)
          /* Fallback and carry on with authentication */
          result = smtp_perform_authentication(conn);
        else {
          failf(data, "STARTTLS not supported.");
          result = CURLE_USE_SSL_FAILED;
        }
      }
      else
        result = smtp_perform_authentication(conn);
    }
  }

  return result;
}