bool
Comm::IsConnOpen(const Comm::ConnectionPointer &conn)
{
    return conn != NULL && conn->isOpen();
}