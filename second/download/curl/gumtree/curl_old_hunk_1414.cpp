	} while (next);
}


/* Curl_infof() is for info message along the way */

void Curl_infof(struct UrlData *data, const char *fmt, ...)
{
  va_list ap;
  if(data->bits.verbose) {
    va_start(ap, fmt);
    fputs("* ", data->err);
    vfprintf(data->err, fmt, ap);
    va_end(ap);
  }
}

/* Curl_failf() is for messages stating why we failed, the LAST one will be
   returned for the user (if requested) */

void Curl_failf(struct UrlData *data, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  if(data->errorbuffer)
    vsnprintf(data->errorbuffer, CURL_ERROR_SIZE, fmt, ap);
  va_end(ap);
}

/* Curl_sendf() sends formated data to the server */
size_t Curl_sendf(int sockfd, struct connectdata *conn,
                  const char *fmt, ...)
{
  struct UrlData *data = conn->data;
  size_t bytes_written;
  char *s;
  va_list ap;
  va_start(ap, fmt);
  s = vaprintf(fmt, ap); /* returns an allocated string */
  va_end(ap);
  if(!s)
    return 0; /* failure */
  if(data->bits.verbose)
    fprintf(data->err, "> %s", s);

  /* Write the buffer to the socket */
  Curl_write(conn, sockfd, s, strlen(s), &bytes_written);

  free(s); /* free the output string */

