bool
Ftp::Server::createDataConnection(Ip::Address cltAddr)
{
    assert(clientConnection != NULL);
    assert(!clientConnection->remote.isAnyAddr());

    if (cltAddr != clientConnection->remote) {
        debugs(33, 2, "rogue PORT " << cltAddr << " request? ctrl: " << clientConnection->remote);
        // Closing the control connection would not help with attacks because
        // the client is evidently able to connect to us. Besides, closing
        // makes retrials easier for the client and more damaging to us.
        setReply(501, "Prohibited parameter value");
        return false;
    }

    closeDataConnection();

    Comm::ConnectionPointer conn = new Comm::Connection();
    conn->flags |= COMM_DOBIND;

    if (clientConnection->flags & COMM_INTERCEPTION) {
        // In the case of NAT interception conn->local value is not set
        // because the TCP stack will automatically pick correct source
        // address for the data connection. We must only ensure that IP
        // version matches client's address.
        conn->local.setAnyAddr();

        if (cltAddr.isIPv4())
            conn->local.setIPv4();

        conn->remote = cltAddr;
    } else {
        // In the case of explicit-proxy the local IP of the control connection
        // is the Squid IP the client is knowingly talking to.
        //
        // In the case of TPROXY the IP address of the control connection is
        // server IP the client is connecting to, it can be spoofed by Squid.
        //
        // In both cases some clients may refuse to accept data connections if
        // these control connectin local-IP's are not used.
        conn->setAddrs(clientConnection->local, cltAddr);

        // Using non-local addresses in TPROXY mode requires appropriate socket option.
        if (clientConnection->flags & COMM_TRANSPARENT)
            conn->flags |= COMM_TRANSPARENT;
    }

    // RFC 959 requires active FTP connections to originate from port 20
    // but that would preclude us from supporting concurrent transfers! (XXX?)
    conn->local.port(0);

    debugs(9, 3, "will actively connect from " << conn->local << " to " <<
           conn->remote);

    dataConn = conn;
    uploadAvailSize = 0;
    return true;
}