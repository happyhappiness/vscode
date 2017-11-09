static CURLcode pop3_state_servergreet_resp(struct connectdata *conn,
                                            int pop3code,
                                            pop3state instate)
{
  CURLcode result = CURLE_OK;
  struct Curl_easy *data = conn->data;
  struct pop3_conn *pop3c = &conn->proto.pop3c;
  const char *line = data->state.buffer;
  size_t len = strlen(line);
  size_t i;

  (void)instate; /* no use for this yet */

  if(pop3code != '+') {
    failf(data, "Got unexpected pop3-server response");
    result = CURLE_WEIRD_SERVER_REPLY;
  }
  else {
    /* Does the server support APOP authentication? */
    if(len >= 4 && line[len - 2] == '>') {
      /* Look for the APOP timestamp */
      for(i = 3; i < len - 2; ++i) {
        if(line[i] == '<') {
          /* Calculate the length of the timestamp */
          size_t timestamplen = len - 1 - i;
          if(!timestamplen)
            break;

          /* Allocate some memory for the timestamp */
          pop3c->apoptimestamp = (char *)calloc(1, timestamplen + 1);

          if(!pop3c->apoptimestamp)
            break;

          /* Copy the timestamp */
          memcpy(pop3c->apoptimestamp, line + i, timestamplen);
          pop3c->apoptimestamp[timestamplen] = '\0';

          /* Store the APOP capability */
          pop3c->authtypes |= POP3_TYPE_APOP;
          break;
        }
      }
    }

    result = pop3_perform_capa(conn);
  }

  return result;
}