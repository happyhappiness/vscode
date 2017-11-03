static int tls_compare_certificates (const gnutls_datum_t *peercert)
{
  gnutls_datum_t cert;
  unsigned char *ptr;
  FILE *fd1;
  int ret;
  gnutls_datum_t b64_data;
  unsigned char *b64_data_data;
  struct stat filestat;

  if (stat(SslCertFile, &filestat) == -1)
    return 0;

  b64_data.size = filestat.st_size+1;
  b64_data_data = (unsigned char *) safe_calloc (1, b64_data.size);
  b64_data_data[b64_data.size-1] = '\0';
  b64_data.data = b64_data_data;

  fd1 = fopen(SslCertFile, "r");
  if (fd1 == NULL) {
    return 0;
  }

  b64_data.size = fread(b64_data.data, 1, b64_data.size, fd1);
  safe_fclose (&fd1);

  do {
    ret = gnutls_pem_base64_decode_alloc(NULL, &b64_data, &cert);
    if (ret != 0)
    {
      FREE (&b64_data_data);
      return 0;
    }

    /* find start of cert, skipping junk */
    ptr = (unsigned char *)strstr((char*)b64_data.data, CERT_SEP);
    if (!ptr)
    {
      gnutls_free(cert.data);
      FREE (&b64_data_data);
      return 0;
    }
    /* find start of next cert */
    ptr = (unsigned char *)strstr((char*)ptr + 1, CERT_SEP);

    b64_data.size = b64_data.size - (ptr - b64_data.data);
    b64_data.data = ptr;

    if (cert.size == peercert->size)
    {
      if (memcmp (cert.data, peercert->data, cert.size) == 0)
      {
	/* match found */
        gnutls_free(cert.data);
	FREE (&b64_data_data);
	return 1;
      }
    }

    gnutls_free(cert.data);
  } while (ptr != NULL);

  /* no match found */
  FREE (&b64_data_data);
  return 0;
}