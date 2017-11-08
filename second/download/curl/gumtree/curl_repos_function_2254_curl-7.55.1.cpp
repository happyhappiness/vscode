static char *ossl_strerror(unsigned long error, char *buf, size_t size)
{
  ERR_error_string_n(error, buf, size);
  return buf;
}