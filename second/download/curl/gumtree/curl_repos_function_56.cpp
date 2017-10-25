int mvsnprintf(char *buffer, size_t maxlength, const char *format, va_list ap_save)
{
  int retcode;
  struct nsprintf info;

  info.buffer = buffer;
  info.length = 0;
  info.max = maxlength;

  retcode = dprintf_formatf(&info, addbyter, format, ap_save);
  info.buffer[0] = 0; /* we terminate this with a zero byte */
  return retcode;
}