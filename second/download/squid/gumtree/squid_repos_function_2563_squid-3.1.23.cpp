void FtpStateData::ftpAcceptDataConnection(const CommAcceptCbParams &io)
{
    char ntoapeer[MAX_IPSTRLEN];
    debugs(9, 3, "ftpAcceptDataConnection");

    if (io.flag == COMM_ERR_CLOSING)
        return;

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        abortTransaction("entry aborted when accepting data conn");
        return;
    }

    if (io.flag != COMM_OK) {
        data.close();
        debugs(9, DBG_IMPORTANT, "FTP AcceptDataConnection: FD " << io.fd << ": " << xstrerr(io.xerrno));
        /** \todo Need to send error message on control channel*/
        ftpFail(this);
        return;
    }

    /** \par
     * When squid.conf ftp_sanitycheck is enabled, check the new connection is actually being
     * made by the remote client which is connected to the FTP control socket.
     * This prevents third-party hacks, but also third-party load balancing handshakes.
     */
    if (Config.Ftp.sanitycheck) {
        io.details.peer.NtoA(ntoapeer,MAX_IPSTRLEN);

        if (strcmp(fd_table[ctrl.fd].ipaddr, ntoapeer) != 0) {
            debugs(9, DBG_IMPORTANT,
                   "FTP data connection from unexpected server (" <<
                   io.details.peer << "), expecting " <<
                   fd_table[ctrl.fd].ipaddr);

            comm_close(io.nfd);
            typedef CommCbMemFunT<FtpStateData, CommAcceptCbParams> acceptDialer;
            AsyncCall::Pointer acceptCall = JobCallback(11, 5,
                                            acceptDialer, this, FtpStateData::ftpAcceptDataConnection);
            comm_accept(data.fd, acceptCall);
            return;
        }
    }

    /**\par
     * Replace the Listen socket with the accepted data socket */
    data.close();
    data.opened(io.nfd, dataCloser());
    data.port = io.details.peer.GetPort();

    io.details.peer.NtoA(ntoapeer,sizeof(ntoapeer));
    data.host = xstrdup(ntoapeer);

    debugs(9, 3, "ftpAcceptDataConnection: Connected data socket on " <<
           "FD " << io.nfd << " to " << io.details.peer << " FD table says: " <<
           "ctrl-peer= " << fd_table[ctrl.fd].ipaddr << ", " <<
           "data-peer= " << fd_table[data.fd].ipaddr);


    AsyncCall::Pointer nullCall = NULL;
    commSetTimeout(ctrl.fd, -1, nullCall);

    typedef CommCbMemFunT<FtpStateData, CommTimeoutCbParams> TimeoutDialer;
    AsyncCall::Pointer timeoutCall =  JobCallback(9, 5,
                                      TimeoutDialer, this, FtpStateData::ftpTimeout);
    commSetTimeout(data.fd, Config.Timeout.read, timeoutCall);

    /*\todo XXX We should have a flag to track connect state...
     *    host NULL -> not connected, port == local port
     *    host set  -> connected, port == remote port
     */
    /* Restart state (SENT_NLST/LIST/RETR) */
    FTP_SM_FUNCS[state] (this);
}