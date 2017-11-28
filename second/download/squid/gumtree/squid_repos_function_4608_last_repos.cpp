void
Ftp::StopListening()
{
    for (AnyP::PortCfgPointer s = FtpPortList; s != NULL; s = s->next) {
        if (s->listenConn != NULL) {
            debugs(1, DBG_IMPORTANT, "Closing FTP port " << s->listenConn->local);
            s->listenConn->close();
            s->listenConn = NULL;
        }
    }
}