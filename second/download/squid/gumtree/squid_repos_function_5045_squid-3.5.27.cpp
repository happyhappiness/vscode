bool
Ftp::Server::checkDataConnPost() const
{
    if (!Comm::IsConnOpen(dataConn)) {
        debugs(33, 3, "missing client data conn: " << dataConn);
        return false;
    }
    return true;
}