static gnutls_x509_crt_fmt_t do_file_type(const char *type)
{
  if(!type || !type[0])
    return GNUTLS_X509_FMT_PEM;
  if(strcasecompare(type, "PEM"))
    return GNUTLS_X509_FMT_PEM;
  if(strcasecompare(type, "DER"))
    return GNUTLS_X509_FMT_DER;
  return -1;
}