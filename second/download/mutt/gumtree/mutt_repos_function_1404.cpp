void mutt_buffer_add (BUFFER* buf, const char* s, size_t len)
{
  size_t offset;

  if (buf->dptr + len + 1 > buf->data + buf->dsize)
  {
    offset = buf->dptr - buf->data;
    buf->dsize += len < 128 ? 128 : len + 1;
    /* suppress compiler aliasing warning */
    safe_realloc ((void**) (void*) &buf->data, buf->dsize);
    buf->dptr = buf->data + offset;
  }
  memcpy (buf->dptr, s, len);
  buf->dptr += len;
  *(buf->dptr) = '\0';
}