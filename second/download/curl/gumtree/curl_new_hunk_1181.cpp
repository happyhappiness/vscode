

#endif

#include "urldata.h"
#include <curl/curl.h>
#include "transfer.h"
#include "sendf.h"
#include "formdata.h"
#include "progress.h"
#include "base64.h"
#include "cookie.h"
#include "strequal.h"
#include "ssluse.h"

#define _MPRINTF_REPLACE /* use our functions only */
#include <curl/mprintf.h>

/* The last #include file should be: */
#ifdef MALLOCDEBUG
#include "memdebug.h"
#endif

/*
 * The add_buffer series of functions are used to build one large memory chunk
 * from repeated function invokes. Used so that the entire HTTP request can
 * be sent in one go.
 */
static CURLcode
 add_buffer(send_buffer *in, void *inptr, size_t size);

/*
 * add_buffer_init() returns a fine buffer struct
 */
static
send_buffer *add_buffer_init(void)
{
  send_buffer *blonk;
  blonk=(send_buffer *)malloc(sizeof(send_buffer));
  if(blonk) {
    memset(blonk, 0, sizeof(send_buffer));
    return blonk;
  }
  return NULL; /* failed, go home */
}

/*
 * add_buffer_send() sends a buffer and frees all associated memory.
 */
static
size_t add_buffer_send(int sockfd, struct connectdata *conn, send_buffer *in)
{
  size_t amount;
  if(conn->data->bits.verbose) {
    fputs("> ", conn->data->err);
    /* this data _may_ contain binary stuff */
    fwrite(in->buffer, in->size_used, 1, conn->data->err);
  }

  Curl_write(conn, sockfd, in->buffer, in->size_used, &amount);

  if(in->buffer)
    free(in->buffer);
  free(in);

  return amount;
}


/* 
 * add_bufferf() builds a buffer from the formatted input
 */
static
CURLcode add_bufferf(send_buffer *in, char *fmt, ...)
{
  CURLcode result = CURLE_OUT_OF_MEMORY;
  char *s;
  va_list ap;
  va_start(ap, fmt);
  s = vaprintf(fmt, ap); /* this allocs a new string to append */
  va_end(ap);

  if(s) {
    result = add_buffer(in, s, strlen(s));
    free(s);
  }
  return result;
}

/*
 * add_buffer() appends a memory chunk to the existing one
 */
static
CURLcode add_buffer(send_buffer *in, void *inptr, size_t size)
{
  char *new_rb;
  int new_size;

  if(size > 0) {
    if(!in->buffer ||
       ((in->size_used + size) > (in->size_max - 1))) {
      new_size = (in->size_used+size)*2;
      if(in->buffer)
        /* we have a buffer, enlarge the existing one */
        new_rb = (char *)realloc(in->buffer, new_size);
      else
        /* create a new buffer */
        new_rb = (char *)malloc(new_size);

      if(!new_rb)
        return CURLE_OUT_OF_MEMORY;

      in->buffer = new_rb;
      in->size_max = new_size;
    }
    memcpy(&in->buffer[in->size_used], inptr, size);
      
    in->size_used += size;
  }

  return CURLE_OK;
}

/* end of the add_buffer functions */
/*****************************************************************************/

/*
 * Read everything until a newline.
 */

static
int GetLine(int sockfd, char *buf, struct connectdata *conn)
{
  size_t nread;
  int read_rc=1;
  char *ptr;
  struct UrlData *data=conn->data;

  ptr=buf;

  /* get us a full line, terminated with a newline */
  for(nread=0;
      (nread<BUFSIZE) && read_rc;
      nread++, ptr++) {
    if((CURLE_OK != Curl_read(conn, sockfd, ptr, 1, &nread)) ||
       (*ptr == '\n'))
      break;
  }
  *ptr=0; /* zero terminate */

  if(data->bits.verbose) {
    fputs("< ", data->err);
    fwrite(buf, 1, nread, data->err);
    fputs("\n", data->err);
  }
  return nread;
}



/*
 * This function checks the linked list of custom HTTP headers for a particular
 * header (prefix).
 */
bool static checkheaders(struct UrlData *data, char *thisheader)
{
  struct curl_slist *head;
