  retcode = dprintf_formatf(&buffer, storebuffer, format, ap_save);
  va_end(ap_save);
  *buffer=0; /* we terminate this with a zero byte */
  return retcode;
}

extern int fputc(int, FILE *);

int curl_mprintf(const char *format, ...)
{
  int retcode;
  va_list ap_save; /* argument pointer */
  va_start(ap_save, format);
