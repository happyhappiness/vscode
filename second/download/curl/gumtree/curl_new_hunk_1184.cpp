  char **buffer = (char **)data;
  **buffer = (char)output;
  (*buffer)++;
  return output; /* act like fputc() ! */
}

int curl_msprintf(char *buffer, const char *format, ...)
{
  va_list ap_save; /* argument pointer */
  int retcode;
  va_start(ap_save, format);
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
  retcode = dprintf_formatf(stdout, fputc, format, ap_save);
  va_end(ap_save);
  return retcode;
}

int curl_mfprintf(FILE *whereto, const char *format, ...)
{
  int retcode;
  va_list ap_save; /* argument pointer */
  va_start(ap_save, format);
  retcode = dprintf_formatf(whereto, fputc, format, ap_save);
  va_end(ap_save);
  return retcode;
}

int curl_mvsprintf(char *buffer, const char *format, va_list ap_save)
{
  int retcode;
  retcode = dprintf_formatf(&buffer, storebuffer, format, ap_save);
  *buffer=0; /* we terminate this with a zero byte */
  return retcode;
}

int curl_mvprintf(const char *format, va_list ap_save)
{
  return dprintf_formatf(stdout, fputc, format, ap_save);
}

int curl_mvfprintf(FILE *whereto, const char *format, va_list ap_save)
{
  return dprintf_formatf(whereto, fputc, format, ap_save);
}

#ifdef DPRINTF_DEBUG
int main()
