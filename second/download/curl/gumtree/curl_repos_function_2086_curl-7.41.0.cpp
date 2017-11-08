static int do_file_type(const char *type)
{
  if(!type || !type[0])
    return SSL_FILETYPE_PEM;
  if(Curl_raw_equal(type, "PEM"))
    return SSL_FILETYPE_PEM;
  if(Curl_raw_equal(type, "DER"))
    return SSL_FILETYPE_ASN1;
  if(Curl_raw_equal(type, "ENG"))
    return SSL_FILETYPE_ENGINE;
  if(Curl_raw_equal(type, "P12"))
    return SSL_FILETYPE_PKCS12;
  return -1;
}