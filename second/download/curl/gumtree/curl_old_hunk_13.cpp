    infop->length++; /* we are now one byte larger */
    return output; /* fputc() returns like this on success */
  }
  return -1;
}

int curl_msnprintf(char *buffer, size_t maxlength, const char *format, ...)
{
  va_list ap_save; /* argument pointer */
  int retcode;
  struct nsprintf info;

  info.buffer = buffer;
  info.length = 0;
  info.max = maxlength;

  va_start(ap_save, format);
  retcode = dprintf_formatf(&info, addbyter, format, ap_save);
  va_end(ap_save);
  info.buffer[0] = 0; /* we terminate this with a zero byte */

  /* we could even return things like */
  
  return retcode;
}

int curl_mvsnprintf(char *buffer, size_t maxlength, const char *format, va_list ap_save)
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


/* fputc() look-alike */
static int alloc_addbyter(int output, FILE *data)
{
  struct asprintf *infop=(struct asprintf *)data;
 
  if(!infop->buffer) {
