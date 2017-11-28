void
Comm::Read(const Comm::ConnectionPointer &conn, AsyncCall::Pointer &callback)
{
    // TODO: move comm_read_base() internals into here
    // when comm_read() char* API is no longer needed
    comm_read_base(conn, NULL, 0, callback);
}