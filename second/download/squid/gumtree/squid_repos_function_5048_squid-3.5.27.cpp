void
Ftp::Server::callException(const std::exception &e)
{
    debugs(33, 2, "FTP::Server job caught: " << e.what());
    closeDataConnection();
    unpinConnection(true);
    if (Comm::IsConnOpen(clientConnection))
        clientConnection->close();
    AsyncJob::callException(e);
}