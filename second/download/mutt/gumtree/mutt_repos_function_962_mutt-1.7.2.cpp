static gnutls_certificate_status_t tls_verify_peers (gnutls_session_t tlsstate)
{
  int verify_ret;
  unsigned int status;

  verify_ret = gnutls_certificate_verify_peers2 (tlsstate, &status);
  if (!verify_ret)
    return status;

  if (status == GNUTLS_E_NO_CERTIFICATE_FOUND)
  {
    mutt_error (_("Unable to get certificate from peer"));
    mutt_sleep (2);
    return 0;
  }
  if (verify_ret < 0)
  {
    mutt_error (_("Certificate verification error (%s)"),
                gnutls_strerror (status));
    mutt_sleep (2);
    return 0;
  }

  /* We only support X.509 certificates (not OpenPGP) at the moment */
  if (gnutls_certificate_type_get (tlsstate) != GNUTLS_CRT_X509)
  {
    mutt_error (_("Certificate is not X.509"));
    mutt_sleep (2);
    return 0;
  }

  return status;
}