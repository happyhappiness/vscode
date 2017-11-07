static int ssl_check_certificate (CONNECTION *conn, sslsockdata *data)
{
  int i, preauthrc, chain_len;
  STACK_OF(X509) *chain;
  X509 *cert;
#ifdef DEBUG
  char buf[STRING];

  dprint (1, (debugfile, "ssl_check_certificate: checking cert %s\n",
              X509_NAME_oneline (X509_get_subject_name (data->cert),
                                 buf, sizeof (buf))));
#endif

  if ((preauthrc = ssl_check_preauth (data->cert, conn->account.host)) > 0)
    return preauthrc;

  chain = SSL_get_peer_cert_chain (data->ssl);
  chain_len = sk_X509_num (chain);
  /* negative preauthrc means the certificate won't be accepted without
   * manual override. */
  if (preauthrc < 0 || !chain || (chain_len <= 1))
    return interactive_check_cert (data->cert, 0, 0);

  /* check the chain from root to peer. */
  for (i = chain_len-1; i >= 0; i--)
  {
    cert = sk_X509_value (chain, i);

    dprint (1, (debugfile, "ssl_check_certificate: checking cert chain entry %s\n",
                X509_NAME_oneline (X509_get_subject_name (cert),
                                   buf, sizeof (buf))));

    /* if the certificate validates or is manually accepted, then add it to
     * the trusted set and recheck the peer certificate */
    if (ssl_check_preauth (cert, NULL)
	|| interactive_check_cert (cert, i, chain_len))
    {
      ssl_cache_trusted_cert (cert);
      if (ssl_check_preauth (data->cert, conn->account.host))
	return 1;
    }
  }

  return 0;
}