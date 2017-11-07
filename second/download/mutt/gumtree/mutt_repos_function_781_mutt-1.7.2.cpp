static int mutt_sasl_conn_read (CONNECTION* conn, char* buf, size_t len)
{
  SASL_DATA* sasldata;
  int rc;

  unsigned int olen;

  sasldata = (SASL_DATA*) conn->sockdata;

  /* if we still have data in our read buffer, copy it into buf */
  if (sasldata->blen > sasldata->bpos)
  {
    olen = (sasldata->blen - sasldata->bpos > len) ? len :
      sasldata->blen - sasldata->bpos;

    memcpy (buf, sasldata->buf+sasldata->bpos, olen);
    sasldata->bpos += olen;

    return olen;
  }
  
  conn->sockdata = sasldata->sockdata;

  sasldata->bpos = 0;
  sasldata->blen = 0;

  /* and decode the result, if necessary */
  if (*sasldata->ssf)
  {
    do
    {
      /* call the underlying read function to fill the buffer */
      rc = (sasldata->msasl_read) (conn, buf, len);
      if (rc <= 0)
	goto out;

      rc = sasl_decode (sasldata->saslconn, buf, rc, &sasldata->buf,
        &sasldata->blen);
      if (rc != SASL_OK)
      {
	dprint (1, (debugfile, "SASL decode failed: %s\n",
          sasl_errstring (rc, NULL, NULL)));
	goto out;
      }
    }
    while (!sasldata->blen);

    olen = (sasldata->blen - sasldata->bpos > len) ? len :
      sasldata->blen - sasldata->bpos;

    memcpy (buf, sasldata->buf, olen);
    sasldata->bpos += olen;

    rc = olen;
  }
  else
    rc = (sasldata->msasl_read) (conn, buf, len);

  out:
    conn->sockdata = sasldata;

    return rc;
}