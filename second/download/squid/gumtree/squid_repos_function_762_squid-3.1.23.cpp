void
ClientHttpRequest::sslBumpStart()
{
    debugs(85, 5, HERE << "ClientHttpRequest::sslBumpStart");

    // send an HTTP 200 response to kick client SSL negotiation
    const int fd = getConn()->fd;
    debugs(33, 7, HERE << "Confirming CONNECT tunnel on FD " << fd);

    // TODO: Unify with tunnel.cc and add a Server(?) header
    static const char *const conn_established =
        "HTTP/1.0 200 Connection established\r\n\r\n";
    comm_write(fd, conn_established, strlen(conn_established),
               &SslBumpEstablish, this, NULL);
}