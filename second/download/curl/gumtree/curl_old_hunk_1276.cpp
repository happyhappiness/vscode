{
  va_list ap_save; /* argument pointer */
  int retcode;
  va_start(ap_save, format);
  retcode = dprintf_formatf(&buffer, storebuffer, format, ap_save);
  va_end(ap_save);
  *buffer=0; /* we terminate this with a zero byte */
  return retcode;
}

int curl_mprintf(const char *format, ...)
{
  int retcode;
