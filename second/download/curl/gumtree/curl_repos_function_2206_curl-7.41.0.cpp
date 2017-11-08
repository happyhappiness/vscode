static int do_file_type(const char *type)
{
  if(!type || !type[0])
    return SSL_FILETYPE_PEM;
  if(Curl_raw_equal(type, "PEM"))
    return SSL_FILETYPE_PEM;
  if(Curl_raw_equal(type, "DER"))
    return SSL_FILETYPE_ASN1;
  return -1;
}