static size_t
buffer_read(struct krb4buffer *buf, void *data, size_t len)
{
    len = min(len, buf->size - buf->index);
    memcpy(data, (char*)buf->data + buf->index, len);
    buf->index += len;
    return len;
}