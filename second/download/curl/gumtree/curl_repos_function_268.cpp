static char *SSL_strerror(unsigned long error, char *buf, size_t size)
{
#ifdef HAVE_ERR_ERROR_STRING_N
  /* OpenSSL 0.9.6 and later has a function named
     ERRO_error_string_n() that takes the size of the buffer as a
     third argument */
  ERR_error_string_n(error, buf, size);
#else
  (void) size;
  ERR_error_string(error, buf);
#endif
  return (buf);
}