int mutt_buffer_printf (BUFFER* buf, const char* fmt, ...)
{
  va_list ap, ap_retry;
  int len, blen, doff;
  
  va_start (ap, fmt);
  va_copy (ap_retry, ap);

  if (!buf->dptr)
    buf->dptr = buf->data;

  doff = buf->dptr - buf->data;
  blen = buf->dsize - doff;
  /* solaris 9 vsnprintf barfs when blen is 0 */
  if (!blen)
  {
    blen = 128;
    buf->dsize += blen;
    safe_realloc (&buf->data, buf->dsize);
    buf->dptr = buf->data + doff;
  }
  if ((len = vsnprintf (buf->dptr, blen, fmt, ap)) >= blen)
  {
    blen = ++len - blen;
    if (blen < 128)
      blen = 128;
    buf->dsize += blen;
    safe_realloc (&buf->data, buf->dsize);
    buf->dptr = buf->data + doff;
    len = vsnprintf (buf->dptr, len, fmt, ap_retry);
  }
  if (len > 0)
    buf->dptr += len;

  va_end (ap);
  va_end (ap_retry);

  return len;
}