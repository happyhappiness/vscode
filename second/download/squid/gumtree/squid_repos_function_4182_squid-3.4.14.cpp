void Adaptation::Icap::ServiceRep::noteConnectionUse(const Comm::ConnectionPointer &conn)
{
    Must(Comm::IsConnOpen(conn));
    fd_table[conn->fd].noteUse(NULL); // pconn re-use but not via PconnPool API
}