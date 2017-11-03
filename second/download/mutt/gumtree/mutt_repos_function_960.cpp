static int tls_check_preauth (const gnutls_datum_t *certdata,
                              gnutls_certificate_status_t certstat,
                              const char *hostname, int chainidx, int* certerr,
                              int* savedcert)
{
  gnutls_x509_crt_t cert;

  *certerr = CERTERR_VALID;
  *savedcert = 0;

  if (gnutls_x509_crt_init (&cert) < 0)
  {
    mutt_error (_("Error initialising gnutls certificate data"));
    mutt_sleep (2);
    return -1;
  }

  if (gnutls_x509_crt_import (cert, certdata, GNUTLS_X509_FMT_DER) < 0)
  {
    mutt_error (_("Error processing certificate data"));
    mutt_sleep (2);
    gnutls_x509_crt_deinit (cert);
    return -1;
  }

  if (option (OPTSSLVERIFYDATES) != MUTT_NO)
  {
    if (gnutls_x509_crt_get_expiration_time (cert) < time(NULL))
      *certerr |= CERTERR_EXPIRED;
    if (gnutls_x509_crt_get_activation_time (cert) > time(NULL))
      *certerr |= CERTERR_NOTYETVALID;
  }

  if (chainidx == 0 && option (OPTSSLVERIFYHOST) != MUTT_NO
      && !gnutls_x509_crt_check_hostname (cert, hostname)
      && !tls_check_stored_hostname (certdata, hostname))
    *certerr |= CERTERR_HOSTNAME;

  /* see whether certificate is in our cache (certificates file) */
  if (tls_compare_certificates (certdata))
  {
    *savedcert = 1;

    if (chainidx == 0 && (certstat & GNUTLS_CERT_INVALID))
    {
      /* doesn't matter - have decided is valid because server
       certificate is in our trusted cache */
      certstat ^= GNUTLS_CERT_INVALID;
    }

    if (chainidx == 0 && (certstat & GNUTLS_CERT_SIGNER_NOT_FOUND))
    {
      /* doesn't matter that we haven't found the signer, since
       certificate is in our trusted cache */
      certstat ^= GNUTLS_CERT_SIGNER_NOT_FOUND;
    }

    if (chainidx <= 1 && (certstat & GNUTLS_CERT_SIGNER_NOT_CA))
    {
      /* Hmm. Not really sure how to handle this, but let's say
       that we don't care if the CA certificate hasn't got the
       correct X.509 basic constraints if server or first signer
       certificate is in our cache. */
      certstat ^= GNUTLS_CERT_SIGNER_NOT_CA;
    }

    if (chainidx == 0 && (certstat & GNUTLS_CERT_INSECURE_ALGORITHM))
    {
      /* doesn't matter that it was signed using an insecure
         algorithm, since certificate is in our trusted cache */
      certstat ^= GNUTLS_CERT_INSECURE_ALGORITHM;
    }
  }

  if (certstat & GNUTLS_CERT_REVOKED)
  {
    *certerr |= CERTERR_REVOKED;
    certstat ^= GNUTLS_CERT_REVOKED;
  }

  if (certstat & GNUTLS_CERT_INVALID)
  {
    *certerr |= CERTERR_NOTTRUSTED;
    certstat ^= GNUTLS_CERT_INVALID;
  }

  if (certstat & GNUTLS_CERT_SIGNER_NOT_FOUND)
  {
    /* NB: already cleared if cert in cache */
    *certerr |= CERTERR_NOTTRUSTED;
    certstat ^= GNUTLS_CERT_SIGNER_NOT_FOUND;
  }

  if (certstat & GNUTLS_CERT_SIGNER_NOT_CA)
  {
    /* NB: already cleared if cert in cache */
    *certerr |= CERTERR_SIGNERNOTCA;
    certstat ^= GNUTLS_CERT_SIGNER_NOT_CA;
  }

  if (certstat & GNUTLS_CERT_INSECURE_ALGORITHM)
  {
    /* NB: already cleared if cert in cache */
    *certerr |= CERTERR_INSECUREALG;
    certstat ^= GNUTLS_CERT_INSECURE_ALGORITHM;
  }

  gnutls_x509_crt_deinit (cert);

  /* we've been zeroing the interesting bits in certstat -
   don't return OK if there are any unhandled bits we don't
   understand */
  if (*certerr == CERTERR_VALID && certstat == 0)
    return 0;

  return -1;
}