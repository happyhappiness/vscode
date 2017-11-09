static int x509_name_oneline(X509_NAME *a, char *buf, size_t size)
{
#if 0
  return X509_NAME_oneline(a, buf, size);
#else
  BIO *bio_out = BIO_new(BIO_s_mem());
  BUF_MEM *biomem;
  int rc;

  if(!bio_out)
    return 1; /* alloc failed! */

  rc = X509_NAME_print_ex(bio_out, a, 0, XN_FLAG_SEP_SPLUS_SPC);
  BIO_get_mem_ptr(bio_out, &biomem);

  if((size_t)biomem->length < size)
    size = biomem->length;
  else
    size--; /* don't overwrite the buffer end */

  memcpy(buf, biomem->data, size);
  buf[size] = 0;

  BIO_free(bio_out);

  return !rc;
#endif
}