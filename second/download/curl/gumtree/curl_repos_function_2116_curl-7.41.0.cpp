static void dumpcert(struct SessionHandle *data, X509 *x, int numcert)
{
  BIO *bio_out = BIO_new(BIO_s_mem());
  BUF_MEM *biomem;

  /* this outputs the cert in this 64 column wide style with newlines and
     -----BEGIN CERTIFICATE----- texts and more */
  PEM_write_bio_X509(bio_out, x);

  BIO_get_mem_ptr(bio_out, &biomem);

  Curl_ssl_push_certinfo_len(data, numcert,
                             "Cert", biomem->data, biomem->length);

  BIO_free(bio_out);
}