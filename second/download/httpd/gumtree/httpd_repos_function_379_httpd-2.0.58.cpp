static void flush_log(buffered_log *buf)
{
    if (buf->outcnt && buf->handle != NULL) {
        apr_file_write(buf->handle, buf->outbuf, &buf->outcnt);
        buf->outcnt = 0;
    }
}