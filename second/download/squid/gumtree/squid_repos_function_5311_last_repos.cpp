void
Ftp::Client::dataClosed(const CommCloseCbParams &)
{
    debugs(9, 4, status());
    if (data.listenConn != NULL) {
        data.listenConn->close();
        data.listenConn = NULL;
        // NP clear() does the: data.fd = -1;
    }
    data.clear();
}