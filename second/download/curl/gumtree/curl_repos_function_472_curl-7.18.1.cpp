static int do_file_type(const char *type)
{
  if(!type || !type[0])
    return SSL_FILETYPE_PEM;
  if(curl_strequal(type, "PEM"))
    return SSL_FILETYPE_PEM;
  if(curl_strequal(type, "DER"))
    return SSL_FILETYPE_ASN1;
  if(curl_strequal(type, "ENG"))
    return SSL_FILETYPE_ENGINE;
  if(curl_strequal(type, "P12"))
    return SSL_FILETYPE_PKCS12;
  return -1;
}