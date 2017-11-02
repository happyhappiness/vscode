static char *
get_buffer(buffer_t * buf, long size)

{
  char * cp;

  /* If `size' >= 0, make sure buffer at `buf' is at least `size'-byte long.
     Return the buffer address. */

  if(size < 0)
    return buf->buf;

  if(!buf->buf) {
    if((buf->buf = malloc(size)))
      buf->size = size;

    return buf->buf;
    }

  if((unsigned long) size <= buf->size) {
    /* Shorten the buffer only if it frees a significant byte count. This
       avoids some realloc() overhead. */

    if(buf->size - size < MIN_BYTE_GAIN)
      return buf->buf;
    }

  /* Resize the buffer. */

  if((cp = realloc(buf->buf, size))) {
    buf->buf = cp;
    buf->size = size;
    }
  else if(size <= buf->size)
    cp = buf->buf;

  return cp;
}