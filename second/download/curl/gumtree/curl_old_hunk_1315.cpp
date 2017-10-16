#include <string.h>
/* The last #include file should be: */
#ifdef MALLOCDEBUG
#include "memdebug.h"
#endif

/* infof() is for info message along the way */

void Curl_infof(struct UrlData *data, char *fmt, ...)
{
  va_list ap;
  if(data->bits.verbose) {
    va_start(ap, fmt);
    fputs("* ", data->err);
    vfprintf(data->err, fmt, ap);
    va_end(ap);
  }
}

/* failf() is for messages stating why we failed, the LAST one will be
   returned for the user (if requested) */

void Curl_failf(struct UrlData *data, char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  if(data->errorbuffer)
    vsnprintf(data->errorbuffer, CURL_ERROR_SIZE, fmt, ap);
  else /* no errorbuffer receives this, write to data->err instead */
    vfprintf(data->err, fmt, ap);
  va_end(ap);
}

/* Curl_sendf() sends formated data to the server */
size_t Curl_sendf(int sockfd, struct connectdata *conn,
                  char *fmt, ...)
