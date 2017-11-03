void mutt_sasl_setup_conn (CONNECTION* conn, sasl_conn_t* saslconn)
{
  SASL_DATA* sasldata = (SASL_DATA*) safe_malloc (sizeof (SASL_DATA));
  /* work around sasl_getprop aliasing issues */
  const void* tmp;

  sasldata->saslconn = saslconn;
  /* get ssf so we know whether we have to (en|de)code read/write */
  sasl_getprop (saslconn, SASL_SSF, &tmp);
  sasldata->ssf = tmp;
  dprint (3, (debugfile, "SASL protection strength: %u\n", *sasldata->ssf));
  /* Add SASL SSF to transport SSF */
  conn->ssf += *sasldata->ssf;
  sasl_getprop (saslconn, SASL_MAXOUTBUF, &tmp);
  sasldata->pbufsize = tmp;
  dprint (3, (debugfile, "SASL protection buffer size: %u\n", *sasldata->pbufsize));

  /* clear input buffer */
  sasldata->buf = NULL;
  sasldata->bpos = 0;
  sasldata->blen = 0;

  /* preserve old functions */
  sasldata->sockdata = conn->sockdata;
  sasldata->msasl_open = conn->conn_open;
  sasldata->msasl_close = conn->conn_close;
  sasldata->msasl_read = conn->conn_read;
  sasldata->msasl_write = conn->conn_write;
  sasldata->msasl_poll = conn->conn_poll;

  /* and set up new functions */
  conn->sockdata = sasldata;
  conn->conn_open = mutt_sasl_conn_open;
  conn->conn_close = mutt_sasl_conn_close;
  conn->conn_read = mutt_sasl_conn_read;
  conn->conn_write = mutt_sasl_conn_write;
  conn->conn_poll = mutt_sasl_conn_poll;
}