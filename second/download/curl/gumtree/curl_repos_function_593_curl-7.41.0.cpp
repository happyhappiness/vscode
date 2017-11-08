static int appenddata(char  **dst_buf,   /* dest buffer */
                      size_t *dst_len,   /* dest buffer data length */
                      size_t *dst_alloc, /* dest buffer allocated size */
                      char   *src_buf,   /* source buffer */
                      int     src_b64)   /* != 0 if source is base64 encoded */
{
  size_t need_alloc = 0;
  size_t src_len = strlen(src_buf);

  if(!src_len)
    return GPE_OK;

  need_alloc = src_len + *dst_len + 1;

  if(src_b64) {
    if(src_buf[src_len - 1] == '\r')
      src_len--;

    if(src_buf[src_len - 1] == '\n')
      src_len--;
  }

  /* enlarge destination buffer if required */
  if(need_alloc > *dst_alloc) {
    size_t newsize = need_alloc * 2;
    char *newptr = realloc(*dst_buf, newsize);
    if(!newptr) {
      return GPE_OUT_OF_MEMORY;
    }
    *dst_alloc = newsize;
    *dst_buf = newptr;
  }

  /* memcpy to support binary blobs */
  memcpy(*dst_buf + *dst_len, src_buf, src_len);
  *dst_len += src_len;
  *(*dst_buf + *dst_len) = '\0';

  return GPE_OK;
}