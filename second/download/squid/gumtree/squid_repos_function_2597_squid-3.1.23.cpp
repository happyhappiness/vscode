void
FtpStateData::closeServer()
{
    debugs(9,3, HERE << "closing FTP server FD " << ctrl.fd << ", Data FD " << data.fd << ", this " << this);

    if (ctrl.fd > -1) {
        fwd->unregister(ctrl.fd);
        ctrl.close();
    }

    data.close();
}