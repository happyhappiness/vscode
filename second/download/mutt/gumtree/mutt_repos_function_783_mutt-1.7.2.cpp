static int mutt_sasl_conn_poll (CONNECTION* conn)
{
  SASL_DATA* sasldata = conn->sockdata;
  int rc;

  conn->sockdata = sasldata->sockdata;
  rc = sasldata->msasl_poll (conn);
  conn->sockdata = sasldata;

  return rc;
}