static int tls_set_priority(tlssockdata *data)
{
  size_t nproto = 0; /* number of tls/ssl protocols */

  if (option(OPTTLSV1_2))
    protocol_priority[nproto++] = GNUTLS_TLS1_2;
  if (option(OPTTLSV1_1))
    protocol_priority[nproto++] = GNUTLS_TLS1_1;
  if (option(OPTTLSV1))
    protocol_priority[nproto++] = GNUTLS_TLS1;
  if (option(OPTSSLV3))
    protocol_priority[nproto++] = GNUTLS_SSL3;
  protocol_priority[nproto] = 0;

  if (nproto == 0)
  {
    mutt_error (_("All available protocols for TLS/SSL connection disabled"));
    return -1;
  }

  if (SslCiphers)
  {
    mutt_error (_("Explicit ciphersuite selection via $ssl_ciphers not supported"));
    mutt_sleep (2);
  }

  /* We use default priorities (see gnutls documentation),
     except for protocol version */
  gnutls_set_default_priority (data->state);
  gnutls_protocol_set_priority (data->state, protocol_priority);
  return 0;
}