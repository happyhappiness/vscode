static int tls_check_certificate (CONNECTION* conn)
{
  tlssockdata *data = conn->sockdata;
  gnutls_session_t state = data->state;
  const gnutls_datum_t *cert_list;
  unsigned int cert_list_size = 0;
  gnutls_certificate_status_t certstat;
  int certerr, i, preauthrc, savedcert, rc = 0;
  int rcpeer = -1; /* the result of tls_check_preauth() on the peer's EE cert */

  if (gnutls_auth_get_type (state) != GNUTLS_CRD_CERTIFICATE)
  {
    mutt_error (_("Unable to get certificate from peer"));
    mutt_sleep (2);
    return 0;
  }

  certstat = tls_verify_peers (state);

  cert_list = gnutls_certificate_get_peers (state, &cert_list_size);
  if (!cert_list)
  {
    mutt_error (_("Unable to get certificate from peer"));
    mutt_sleep (2);
    return 0;
  }

  /* tls_verify_peers doesn't check hostname or expiration, so walk
   * from most specific to least checking these. If we see a saved certificate,
   * its status short-circuits the remaining checks. */
  preauthrc = 0;
  for (i = 0; i < cert_list_size; i++) {
    rc = tls_check_preauth(&cert_list[i], certstat, conn->account.host, i,
                           &certerr, &savedcert);
    preauthrc += rc;
    if (i == 0)
    {
      /* This is the peer's end-entity X.509 certificate.  Stash the result
       * to check later in this function.
       */
      rcpeer = rc;
    }

    if (savedcert)
    {
      if (!preauthrc)
        return 1;
      else
        break;
    }
  }

  /* then check interactively, starting from chain root */
  for (i = cert_list_size - 1; i >= 0; i--)
  {
    rc = tls_check_one_certificate (&cert_list[i], certstat, conn->account.host,
                                    i, cert_list_size);

    /* add signers to trust set, then reverify */
    if (i && rc) {
      rc = gnutls_certificate_set_x509_trust_mem (data->xcred, &cert_list[i],
                                                  GNUTLS_X509_FMT_DER);
      if (rc != 1)
        dprint (1, (debugfile, "error trusting certificate %d: %d\n", i, rc));

      certstat = tls_verify_peers (state);
      /* If the cert chain now verifies, and the peer's cert was otherwise
       * valid (rcpeer==0), we are done.
       */
      if (!certstat && !rcpeer)
        return 1;
    }
  }

  return rc;
}