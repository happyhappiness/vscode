static int mutt_sasl_conn_open (CONNECTION* conn)
{
  SASL_DATA* sasldata;
  int rc;

  sasldata = (SASL_DATA*) conn->sockdata;
  conn->sockdata = sasldata->sockdata;
  rc = (sasldata->msasl_open) (conn);
  conn->sockdata = sasldata;

  return rc;
}