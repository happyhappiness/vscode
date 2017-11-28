void
comm_write_mbuf(int fd, MemBuf *mb, IOCB * handler, void *handler_data)
{
    comm_write(fd, mb->buf, mb->size, handler, handler_data, mb->freeFunc());
}