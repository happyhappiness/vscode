char *mvaprintf(const char *format, va_list ap_save)
{
  int retcode;
  struct asprintf info;

  info.buffer = NULL;
  info.len = 0;
  info.alloc = 0;

  retcode = dprintf_formatf(&info, alloc_addbyter, format, ap_save);
  info.buffer[info.len] = 0; /* we terminate this with a zero byte */
  if(info.len) {
    info.buffer[info.len] = 0; /* we terminate this with a zero byte */
    return info.buffer;
  }
  else
    return NULL;
}