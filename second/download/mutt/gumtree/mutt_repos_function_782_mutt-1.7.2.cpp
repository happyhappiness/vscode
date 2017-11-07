static int mutt_sasl_conn_write (CONNECTION* conn, const char* buf,
  size_t len)
{
  SASL_DATA* sasldata;
  int rc;

  const char *pbuf;
  unsigned int olen, plen;

  sasldata = (SASL_DATA*) conn->sockdata;
  conn->sockdata = sasldata->sockdata;

  /* encode data, if necessary */
  if (*sasldata->ssf)
  {
    /* handle data larger than MAXOUTBUF */
    do
    {
      olen = (len > *sasldata->pbufsize) ? *sasldata->pbufsize : len;

      rc = sasl_encode (sasldata->saslconn, buf, olen, &pbuf, &plen);
      if (rc != SASL_OK)
      {
	dprint (1, (debugfile, "SASL encoding failed: %s\n",
          sasl_errstring (rc, NULL, NULL)));
	goto fail;
      }

      rc = (sasldata->msasl_write) (conn, pbuf, plen);
      if (rc != plen)
	goto fail;

      len -= olen;
      buf += olen;
    }
    while (len > *sasldata->pbufsize);
  }
  else
  /* just write using the underlying socket function */
    rc = (sasldata->msasl_write) (conn, buf, len);
  
  conn->sockdata = sasldata;

  return rc;

 fail:
  conn->sockdata = sasldata;
  return -1;
}