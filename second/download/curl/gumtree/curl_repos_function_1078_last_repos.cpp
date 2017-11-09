static bool http2_connisdead(struct connectdata *check)
{
  int sval;
  bool ret_val = TRUE;

  sval = SOCKET_READABLE(check->sock[FIRSTSOCKET], 0);
  if(sval == 0) {
    /* timeout */
    ret_val = FALSE;
  }
  else if(sval & CURL_CSELECT_ERR) {
    /* socket is in an error state */
    ret_val = TRUE;
  }
  else if(sval & CURL_CSELECT_IN) {
    /* readable with no error. could still be closed */
    ret_val = !Curl_connalive(check);
  }

  return ret_val;
}