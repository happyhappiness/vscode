size_t Curl_gtls_version(char *buffer, size_t size)
{
  return snprintf(buffer, size, "GnuTLS/%s", gnutls_check_version(NULL));
}