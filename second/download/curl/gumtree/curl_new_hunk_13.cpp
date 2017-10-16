    infop->length++; /* we are now one byte larger */
    return output; /* fputc() returns like this on success */
  }
  return -1;
}

int curl_mvsnprintf(char *buffer, size_t maxlength, const char *format,
                    va_list ap_save)
{
  int retcode;
  struct nsprintf info;

  info.buffer = buffer;
  info.length = 0;
  info.max = maxlength;

  retcode = dprintf_formatf(&info, addbyter, format, ap_save);
  if(info.max) {
    /* we terminate this with a zero byte */
    if(info.max == info.length)
      /* we're at maximum, scrap the last letter */
      info.buffer[-1] = 0;
    else
      info.buffer[0] = 0;
  }
  return retcode;
}

int curl_msnprintf(char *buffer, size_t maxlength, const char *format, ...)
{
  int retcode;
  va_list ap_save; /* argument pointer */
  va_start(ap_save, format);
  retcode = curl_mvsnprintf(buffer, maxlength, format, ap_save);
  va_end(ap_save);
  return retcode;
}

/* fputc() look-alike */
static int alloc_addbyter(int output, FILE *data)
{
  struct asprintf *infop=(struct asprintf *)data;
 
  if(!infop->buffer) {
