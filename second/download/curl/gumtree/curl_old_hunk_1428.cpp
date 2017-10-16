	} while (next);
}


/* Curl_infof() is for info message along the way */

void Curl_infof(struct UrlData *data, char *fmt, ...)
{
  va_list ap;
  if(data->bits.verbose) {
    va_start(ap, fmt);
    fputs("* ", data->err);
    vfprintf(data->err, fmt, ap);
