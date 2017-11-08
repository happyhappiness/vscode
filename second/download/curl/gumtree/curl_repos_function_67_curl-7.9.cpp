static int Get_SSL_Session(struct connectdata *conn,
                           SSL_SESSION **ssl_sessionid)
{
  struct curl_ssl_session *check;
  struct SessionHandle *data = conn->data;
  long i;

  for(i=0; i< data->set.ssl.numsessions; i++) {
    check = &data->state.session[i];
    if(!check->sessionid)
      /* not session ID means blank entry */
      continue;
    if(strequal(conn->name, check->name) &&
       (conn->remote_port == check->remote_port) ) {
      /* yes, we have a session ID! */
      data->state.sessionage++;            /* increase general age */
      check->age = data->state.sessionage; /* set this as used in this age */
      *ssl_sessionid = check->sessionid;
      return FALSE;
    }
  }
  *ssl_sessionid = (SSL_SESSION *)NULL;
  return TRUE;
}