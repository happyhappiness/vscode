void
ClientHttpRequest::sslBumpEstablish(comm_err_t errflag)
{
    // Bail out quickly on COMM_ERR_CLOSING - close handlers will tidy up
    if (errflag == COMM_ERR_CLOSING)
        return;

    if (errflag) {
        debugs(85, 3, HERE << "CONNECT response failure in SslBump: " << errflag);
        comm_close(getConn()->fd);
        return;
    }

    getConn()->switchToHttps(request->GetHost());
}