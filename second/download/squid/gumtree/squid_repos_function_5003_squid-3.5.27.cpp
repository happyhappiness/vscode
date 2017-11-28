void
Ftp::Server::closeDataConnection()
{
    if (listener != NULL) {
        listener->cancel("no longer needed");
        listener = NULL;
    }

    if (Comm::IsConnOpen(dataListenConn)) {
        debugs(33, 5, "FTP closing client data listen socket: " <<
               *dataListenConn);
        dataListenConn->close();
    }
    dataListenConn = NULL;

    if (reader != NULL) {
        // Comm::ReadCancel can deal with negative FDs
        Comm::ReadCancel(dataConn->fd, reader);
        reader = NULL;
    }

    if (Comm::IsConnOpen(dataConn)) {
        debugs(33, 5, "FTP closing client data connection: " <<
               *dataConn);
        dataConn->close();
    }
    dataConn = NULL;
}