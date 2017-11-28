static void
ftpSendPORT(FtpStateData * ftpState)
{
    /* check the server control channel is still available */
    if (!ftpState || !ftpState->haveControlChannel("ftpSendPort"))
        return;

    if (Config.Ftp.epsv_all && ftpState->flags.epsv_all_sent) {
        debugs(9, DBG_IMPORTANT, "FTP does not allow PORT method after 'EPSV ALL' has been sent.");
        return;
    }

    debugs(9, 3, HERE);
    ftpState->flags.pasv_supported = 0;
    ftpOpenListenSocket(ftpState, 0);

    if (!Comm::IsConnOpen(ftpState->data.listenConn)) {
        if ( ftpState->data.listenConn != NULL && !ftpState->data.listenConn->local.IsIPv4() ) {
            /* non-IPv4 CANNOT send PORT command.                       */
            /* we got here by attempting and failing an EPRT            */
            /* using the same reply code should simulate a PORT failure */
            ftpReadPORT(ftpState);
            return;
        }

        /* XXX Need to set error message */
        ftpFail(ftpState);
        return;
    }

    // pull out the internal IP address bytes to send in PORT command...
    // source them from the listen_conn->local

    struct addrinfo *AI = NULL;
    ftpState->data.listenConn->local.GetAddrInfo(AI, AF_INET);
    unsigned char *addrptr = (unsigned char *) &((struct sockaddr_in*)AI->ai_addr)->sin_addr;
    unsigned char *portptr = (unsigned char *) &((struct sockaddr_in*)AI->ai_addr)->sin_port;
    snprintf(cbuf, CTRL_BUFLEN, "PORT %d,%d,%d,%d,%d,%d\r\n",
             addrptr[0], addrptr[1], addrptr[2], addrptr[3],
             portptr[0], portptr[1]);
    ftpState->writeCommand(cbuf);
    ftpState->state = SENT_PORT;

    ftpState->data.listenConn->local.FreeAddrInfo(AI);
}