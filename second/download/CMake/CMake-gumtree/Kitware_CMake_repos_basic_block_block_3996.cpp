{
  CURLcode result=CURLE_OK;
  struct Curl_easy *data=conn->data;
  curl_socket_t sockfd = conn->sock[FIRSTSOCKET];

  curl_off_t *bytecount = &data->req.bytecount;
  char *path = data->state.path;
  char *sel = NULL;
  char *sel_org = NULL;
  ssize_t amount, k;
  size_t len;

  *done = TRUE; /* unconditionally */

  /* Create selector. Degenerate cases: / and /1 => convert to "" */
  if(strlen(path) <= 2) {
    sel = (char *)"";
    len = (int)strlen(sel);
  }
  else {
    char *newp;
    size_t j, i;

    /* Otherwise, drop / and the first character (i.e., item type) ... */
    newp = path;
    newp+=2;

    /* ... then turn ? into TAB for search servers, Veronica, etc. ... */
    j = strlen(newp);
    for(i=0; i<j; i++)
      if(newp[i] == '?')
        newp[i] = '\x09';

    /* ... and finally unescape */
    result = Curl_urldecode(data, newp, 0, &sel, &len, FALSE);
    if(result)
      return result;
    sel_org = sel;
  }

  /* We use Curl_write instead of Curl_sendf to make sure the entire buffer is
     sent, which could be sizeable with long selectors. */
  k = curlx_uztosz(len);

  for(;;) {
    result = Curl_write(conn, sockfd, sel, k, &amount);
    if(!result) { /* Which may not have written it all! */
      result = Curl_client_write(conn, CLIENTWRITE_HEADER, sel, amount);
      if(result)
        break;

      k -= amount;
      sel += amount;
      if(k < 1)
        break; /* but it did write it all */
    }
    else
      break;

    /* Don't busyloop. The entire loop thing is a work-around as it causes a
       BLOCKING behavior which is a NO-NO. This function should rather be
       split up in a do and a doing piece where the pieces that aren't
       possible to send now will be sent in the doing function repeatedly
       until the entire request is sent.

       Wait a while for the socket to be writable. Note that this doesn't
       acknowledge the timeout.
    */
    if(SOCKET_WRITABLE(sockfd, 100) < 0) {
      result = CURLE_SEND_ERROR;
      break;
    }
  }

  free(sel_org);

  if(!result)
    /* We can use Curl_sendf to send the terminal \r\n relatively safely and
       save allocing another string/doing another _write loop. */
    result = Curl_sendf(sockfd, conn, "\r\n");
  if(result) {
    failf(data, "Failed sending Gopher request");
    return result;
  }
  result = Curl_client_write(conn, CLIENTWRITE_HEADER, (char *)"\r\n", 2);
  if(result)
    return result;

  Curl_setup_transfer(conn, FIRSTSOCKET, -1, FALSE, bytecount,
                      -1, NULL); /* no upload */
  return CURLE_OK;
}