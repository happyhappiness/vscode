bool
Ftp::Client::handlePasvReply(Ip::Address &srvAddr)
{
    int code = ctrl.replycode;
    char *buf;
    debugs(9, 3, status());

    if (!Comm::IsConnOpen(ctrl.conn)) {
        debugs(9, 5, "The control connection to the remote end is closed");
        return false;
    }

    if (code != 227) {
        debugs(9, 2, "PASV not supported by remote end");
        return false;
    }

    /*  227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).  */
    /*  ANSI sez [^0-9] is undefined, it breaks on Watcom cc */
    debugs(9, 5, "scanning: " << ctrl.last_reply);

    buf = ctrl.last_reply + strcspn(ctrl.last_reply, "0123456789");

    const char *forceIp = Config.Ftp.sanitycheck ?
                          fd_table[ctrl.conn->fd].ipaddr : NULL;
    if (!Ftp::ParseIpPort(buf, forceIp, srvAddr)) {
        debugs(9, DBG_IMPORTANT, "Unsafe PASV reply from " <<
               ctrl.conn->remote << ": " << ctrl.last_reply);
        return false;
    }

    data.addr(srvAddr);

    return true;
}