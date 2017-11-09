static int mutt_sasl_conn_poll (CONNECTION* conn, time_t wait_secs)
{
  SASL_DATA* sasldata = conn->sockdata;
  int rc;

  conn->sockdata = sasldata->sockdata;
  rc = sasldata->msasl_poll (conn, wait_secs);
  conn->sockdata = sasldata;

  return rc;
}