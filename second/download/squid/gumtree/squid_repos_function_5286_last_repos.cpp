void
Ftp::Relay::abort(void *d)
{
    Ftp::Relay *ftpClient = (Ftp::Relay *)d;
    debugs(9, 2, "Client Data connection closed!");
    if (!cbdataReferenceValid(ftpClient))
        return;
    if (Comm::IsConnOpen(ftpClient->data.conn))
        ftpClient->dataComplete();
}