static gnutls_x509_crt_fmt do_file_type(const char *type)
{
  if(!type || !type[0])
    return GNUTLS_X509_FMT_PEM;
  if(curl_strequal(type, "PEM"))
    return GNUTLS_X509_FMT_PEM;
  if(curl_strequal(type, "DER"))
    return GNUTLS_X509_FMT_DER;
  return -1;
}