void Adaptation::Icap::ServiceRep::noteConnectionUse(const Comm::ConnectionPointer &conn)
{
    Must(Comm::IsConnOpen(conn));
    fd_table[conn->fd].noteUse(); // pconn re-use, albeit not via PconnPool API
}