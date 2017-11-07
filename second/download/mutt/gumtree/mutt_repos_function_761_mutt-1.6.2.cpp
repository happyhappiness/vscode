static int mutt_sasl_conn_close (CONNECTION* conn)
{
  SASL_DATA* sasldata;
  int rc;

  sasldata = (SASL_DATA*) conn->sockdata;

  /* restore connection's underlying methods */
  conn->sockdata = sasldata->sockdata;
  conn->conn_open = sasldata->msasl_open;
  conn->conn_close = sasldata->msasl_close;
  conn->conn_read = sasldata->msasl_read;
  conn->conn_write = sasldata->msasl_write;
  conn->conn_poll = sasldata->msasl_poll;

  /* release sasl resources */
  sasl_dispose (&sasldata->saslconn);
  FREE (&sasldata);

  /* call underlying close */
  rc = (conn->conn_close) (conn);

  return rc;
}