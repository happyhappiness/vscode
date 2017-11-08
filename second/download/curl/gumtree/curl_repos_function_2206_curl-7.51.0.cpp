static char *ossl_strerror(unsigned long error, char *buf, size_t size)
{
  /* OpenSSL 0.9.6 and later has a function named
     ERR_error_string_n() that takes the size of the buffer as a
     third argument */
  ERR_error_string_n(error, buf, size);
  return buf;
}