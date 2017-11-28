void
ConnectStateData::connect()
{
    defaults();

    debugs(5,5, HERE << "to " << S);

    switch (comm_connect_addr(fd, S) ) {

    case COMM_INPROGRESS:
        debugs(5, 5, HERE << "FD " << fd << ": COMM_INPROGRESS");
        commSetSelect(fd, COMM_SELECT_WRITE, ConnectStateData::Connect, this, 0);
        break;

    case COMM_OK:
        debugs(5, 5, HERE << "FD " << fd << ": COMM_OK - connected");
        ipcacheMarkGoodAddr(host, S);
        callCallback(COMM_OK, 0);
        break;

    case COMM_ERR_PROTOCOL:
        debugs(5, 5, HERE "FD " << fd << ": COMM_ERR_PROTOCOL - try again");
        /* problem using the desired protocol over this socket.
         * skip to the next address and hope it's more compatible
         * but do not mark the current address as bad
         */
        tries++;
        if (commRetryConnect()) {
            /* Force an addr cycle to move forward to the next possible address */
            ipcacheCycleAddr(host, NULL);
            eventAdd("commReconnect", commReconnect, this, this->addrcount == 1 ? 0.05 : 0.0, 0);
        } else {
            debugs(5, 5, HERE << "FD " << fd << ": COMM_ERR_PROTOCOL - ERR tried too many times already.");
            callCallback(COMM_ERR_CONNECT, errno);
        }
        break;

    default:
        debugs(5, 5, HERE "FD " << fd << ": * - try again");
        tries++;
        ipcacheMarkBadAddr(host, S);

#if USE_ICMP
        if (Config.onoff.test_reachability)
            netdbDeleteAddrNetwork(S);
#endif

        if (commRetryConnect()) {
            eventAdd("commReconnect", commReconnect, this, this->addrcount == 1 ? 0.05 : 0.0, 0);
        } else {
            debugs(5, 5, HERE << "FD " << fd << ": * - ERR tried too many times already.");
            callCallback(COMM_ERR_CONNECT, errno);
        }
    }
}