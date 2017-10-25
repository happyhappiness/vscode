char *maprintf(const char *format, ...)
{
  va_list ap_save; /* argument pointer */
  int retcode;
  struct asprintf info;

  info.buffer = NULL;
  info.len = 0;
  info.alloc = 0;

  va_start(ap_save, format);
  retcode = dprintf_formatf(&info, alloc_addbyter, format, ap_save);
  va_end(ap_save);
  if(info.len) {
    info.buffer[info.len] = 0; /* we terminate this with a zero byte */
    return info.buffer;
  }
  else
    return NULL;
}