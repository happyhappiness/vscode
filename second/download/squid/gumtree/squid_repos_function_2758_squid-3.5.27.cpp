void
TunnelStateData::Connection::write(const char *b, int size, AsyncCall::Pointer &callback, FREE * free_func)
{
    writer = callback;
    Comm::Write(conn, b, size, callback, free_func);
}