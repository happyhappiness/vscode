static int is_fatal_error(int code)
{
  switch(code) {
  /* TODO: Should CURLE_SSL_CACERT be included as critical error ? */
  case CURLE_FAILED_INIT:
  case CURLE_OUT_OF_MEMORY:
  case CURLE_UNKNOWN_OPTION:
  case CURLE_FUNCTION_NOT_FOUND:
  case CURLE_BAD_FUNCTION_ARGUMENT:
    /* critical error */
    return 1;
  default:
    break;
  }
  /* no error or not critical */
  return 0;
}