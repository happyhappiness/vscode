  }
#endif

  return bytes_written;
}

/*
 * add_buffer_init() returns a fine buffer struct
 */
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
size_t add_buffer_send(int sockfd, struct connectdata *conn, send_buffer *in)
{
  size_t amount;
  if(conn->data->bits.verbose) {
    fputs("> ", conn->data->err);
    /* this data _may_ contain binary stuff */
    fwrite(in->buffer, in->size_used, 1, conn->data->err);
  }

  amount = ssend(sockfd, conn, in->buffer, in->size_used);

  if(in->buffer)
    free(in->buffer);
  free(in);

  return amount;
}


/* 
 * add_bufferf() builds a buffer from the formatted input
 */
CURLcode add_bufferf(send_buffer *in, char *fmt, ...)
{
  CURLcode result = CURLE_OUT_OF_MEMORY;
  char *s;
  va_list ap;
  va_start(ap, fmt);
  s = mvaprintf(fmt, ap); /* this allocs a new string to append */
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

