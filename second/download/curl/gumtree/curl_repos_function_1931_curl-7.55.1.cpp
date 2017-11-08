static size_t
buffer_read(struct krb5buffer *buf, void *data, size_t len)
{
  if(buf->size - buf->index < len)
    len = buf->size - buf->index;
  memcpy(data, (char *)buf->data + buf->index, len);
  buf->index += len;
  return len;
}