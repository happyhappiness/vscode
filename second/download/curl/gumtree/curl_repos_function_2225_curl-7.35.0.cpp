static gnutls_x509_crt_fmt do_file_type(const char *type)
{
  if(!type || !type[0])
    return GNUTLS_X509_FMT_PEM;
  if(Curl_raw_equal(type, "PEM"))
    return GNUTLS_X509_FMT_PEM;
  if(Curl_raw_equal(type, "DER"))
    return GNUTLS_X509_FMT_DER;
  return -1;
}