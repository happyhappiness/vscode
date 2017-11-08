static char *getcurlcodestr(int cc)
{
  char *buf = malloc(256);
  if(buf) {
    snprintf(buf, 256, "%s (%d)",
      (cc == SANITIZE_ERR_OK ? "SANITIZE_ERR_OK" :
       cc == SANITIZE_ERR_BAD_ARGUMENT ? "SANITIZE_ERR_BAD_ARGUMENT" :
       cc == SANITIZE_ERR_INVALID_PATH ? "SANITIZE_ERR_INVALID_PATH" :
       cc == SANITIZE_ERR_OUT_OF_MEMORY ? "SANITIZE_ERR_OUT_OF_MEMORY" :
       "unexpected error code - add name"),
      cc);
  }
  return buf;
}