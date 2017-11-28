void
Comm::Write(const Comm::ConnectionPointer &conn, MemBuf *mb, AsyncCall::Pointer &callback)
{
    Comm::Write(conn, mb->buf, mb->size, callback, mb->freeFunc());
}