static int tls_negotiate (CONNECTION * conn)
{
  tlssockdata *data;
  int err;

  data = (tlssockdata *) safe_calloc (1, sizeof (tlssockdata));
  conn->sockdata = data;
  err = gnutls_certificate_allocate_credentials (&data->xcred);
  if (err < 0)
  {
    FREE(&conn->sockdata);
    mutt_error ("gnutls_certificate_allocate_credentials: %s", gnutls_strerror(err));
    mutt_sleep (2);
    return -1;
  }

  gnutls_certificate_set_x509_trust_file (data->xcred, SslCertFile,
					  GNUTLS_X509_FMT_PEM);
  /* ignore errors, maybe file doesn't exist yet */

  if (SslCACertFile)
  {
    gnutls_certificate_set_x509_trust_file (data->xcred, SslCACertFile,
                                            GNUTLS_X509_FMT_PEM);
  }

  if (SslClientCert)
  {
    dprint (2, (debugfile, "Using client certificate %s\n", SslClientCert));
    gnutls_certificate_set_x509_key_file (data->xcred, SslClientCert,
                                          SslClientCert, GNUTLS_X509_FMT_PEM);
  }

#if HAVE_DECL_GNUTLS_VERIFY_DISABLE_TIME_CHECKS
  /* disable checking certificate activation/expiration times
     in gnutls, we do the checks ourselves */
  gnutls_certificate_set_verify_flags(data->xcred, GNUTLS_VERIFY_DISABLE_TIME_CHECKS);
#endif

  if ((err = gnutls_init(&data->state, GNUTLS_CLIENT)))
  {
    mutt_error ("gnutls_handshake: %s", gnutls_strerror(err));
    mutt_sleep (2);
    goto fail;
  }

  /* set socket */
  gnutls_transport_set_ptr (data->state, (gnutls_transport_ptr_t)(long)conn->fd);

  if (gnutls_server_name_set (data->state, GNUTLS_NAME_DNS, conn->account.host,
                              mutt_strlen (conn->account.host)))
  {
    mutt_error _("Warning: unable to set TLS SNI host name");
    mutt_sleep (1);
  }

  if (tls_set_priority(data) < 0) {
    goto fail;
  }

  if (SslDHPrimeBits > 0)
  {
    gnutls_dh_set_prime_bits (data->state, SslDHPrimeBits);
  }

/*
  gnutls_set_cred (data->state, GNUTLS_ANON, NULL);
*/

  gnutls_credentials_set (data->state, GNUTLS_CRD_CERTIFICATE, data->xcred);

  err = gnutls_handshake(data->state);

  while (err == GNUTLS_E_AGAIN || err == GNUTLS_E_INTERRUPTED)
  {
    err = gnutls_handshake(data->state);
  }
  if (err < 0) {
    if (err == GNUTLS_E_FATAL_ALERT_RECEIVED)
    {
      mutt_error("gnutls_handshake: %s(%s)", gnutls_strerror(err),
		 gnutls_alert_get_name(gnutls_alert_get(data->state)));
    }
    else
    {
      mutt_error("gnutls_handshake: %s", gnutls_strerror(err));
    }
    mutt_sleep (2);
    goto fail;
  }

  if (!tls_check_certificate(conn))
    goto fail;

  /* set Security Strength Factor (SSF) for SASL */
  /* NB: gnutls_cipher_get_key_size() returns key length in bytes */
  conn->ssf = gnutls_cipher_get_key_size (gnutls_cipher_get (data->state)) * 8;

  tls_get_client_cert (conn);

  if (!option(OPTNOCURSES)) {
    mutt_message (_("SSL/TLS connection using %s (%s/%s/%s)"),
                  gnutls_protocol_get_name (gnutls_protocol_get_version (data->state)),
                  gnutls_kx_get_name (gnutls_kx_get (data->state)),
                  gnutls_cipher_get_name (gnutls_cipher_get (data->state)),
                  gnutls_mac_get_name (gnutls_mac_get (data->state)));
    mutt_sleep (0);
  }

  return 0;

 fail:
  gnutls_certificate_free_credentials (data->xcred);
  gnutls_deinit (data->state);
  FREE(&conn->sockdata);
  return -1;
}