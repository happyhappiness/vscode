static int mutt_sasl_conn_close (CONNECTION* conn)
{
  SASL_DATA* sasldata;
  int rc;

  sasldata = (SASL_DATA*) conn->sockdata;

  /* restore connection's underlying methods */
  conn->sockdata = sasldata->sockdata;
  conn->open = sasldata->open;
  conn->close = sasldata->close;
  conn->read = sasldata->read;
  conn->write = sasldata->write;

  /* release sasl resources */
  sasl_dispose (&sasldata->saslconn);
  FREE (&sasldata->buf);
  FREE (&sasldata);

  /* call underlying close */
  rc = (conn->close) (conn);

  return rc;
}