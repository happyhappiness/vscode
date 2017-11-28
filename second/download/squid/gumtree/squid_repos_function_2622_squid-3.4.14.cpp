void
FtpStateData::closeServer()
{
    if (Comm::IsConnOpen(ctrl.conn)) {
        debugs(9,3, HERE << "closing FTP server FD " << ctrl.conn->fd << ", this " << this);
        fwd->unregister(ctrl.conn);
        ctrl.close();
    }

    if (Comm::IsConnOpen(data.conn)) {
        debugs(9,3, HERE << "closing FTP data FD " << data.conn->fd << ", this " << this);
        data.close();
    }

    debugs(9,3, HERE << "FTP ctrl and data connections closed. this " << this);
}