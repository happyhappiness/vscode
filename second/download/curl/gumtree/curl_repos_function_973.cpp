bool Curl_rtsp_connisdead(struct connectdata *check)
{
  int sval;
  bool ret_val = TRUE;

  sval = Curl_socket_ready(check->sock[FIRSTSOCKET], CURL_SOCKET_BAD, 0);
  if(sval == 0) {
    /* timeout */
    ret_val = FALSE;
  }
  else if(sval & CURL_CSELECT_ERR) {
    /* socket is in an error state */
    ret_val = TRUE;
  }
  else if((sval & CURL_CSELECT_IN) && check->data) {
    /* readable with no error. could be closed or could be alive but we can
       only check if we have a proper SessionHandle for the connection */
    curl_socket_t connectinfo = Curl_getconnectinfo(check->data, &check);
    if(connectinfo != CURL_SOCKET_BAD)
      ret_val = FALSE;
  }

  return ret_val;
}