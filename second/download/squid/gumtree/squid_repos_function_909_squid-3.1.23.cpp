void
comm_write_mbuf(int fd, MemBuf *mb, AsyncCall::Pointer &callback)
{
    comm_write(fd, mb->buf, mb->size, callback, mb->freeFunc());
}