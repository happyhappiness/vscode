static bool pop3_endofresp(struct connectdata *conn, char *line, size_t len,
                           int *resp)
{
  struct pop3_conn *pop3c = &conn->proto.pop3c;

  /* Do we have an error response? */
  if(len >= 4 && !memcmp("-ERR", line, 4)) {
    *resp = '-';

    return TRUE;
  }

  /* Are we processing CAPA command responses? */
  if(pop3c->state == POP3_CAPA) {
    /* Do we have the terminating line? */
    if(len >= 1 && !memcmp(line, ".", 1))
      /* Treat the response as a success */
      *resp = '+';
    else
      /* Treat the response as an untagged continuation */
      *resp = '*';

    return TRUE;
  }

  /* Do we have a success response? */
  if(len >= 3 && !memcmp("+OK", line, 3)) {
    *resp = '+';

    return TRUE;
  }

  /* Do we have a continuation response? */
  if(len >= 1 && !memcmp("+", line, 1)) {
    *resp = '*';

    return TRUE;
  }

  return FALSE; /* Nothing for us */
}