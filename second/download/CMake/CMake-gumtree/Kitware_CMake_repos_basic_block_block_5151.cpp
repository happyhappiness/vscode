{
  /* we have a piece of a command still left to send */
  struct connectdata *conn = pp->conn;
  ssize_t written;
  curl_socket_t sock = conn->sock[FIRSTSOCKET];
  CURLcode result = Curl_write(conn, sock, pp->sendthis + pp->sendsize -
                               pp->sendleft, pp->sendleft, &written);
  if(result)
    return result;

  if(written != (ssize_t)pp->sendleft) {
    /* only a fraction was sent */
    pp->sendleft -= written;
  }
  else {
    free(pp->sendthis);
    pp->sendthis=NULL;
    pp->sendleft = pp->sendsize = 0;
    pp->response = Curl_tvnow();
  }
  return CURLE_OK;
}