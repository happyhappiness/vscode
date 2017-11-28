bool
connIsUsable(ConnStateData * conn)
{
    if (conn == NULL || !cbdataReferenceValid(conn) || !Comm::IsConnOpen(conn->clientConnection))
        return false;

    return true;
}