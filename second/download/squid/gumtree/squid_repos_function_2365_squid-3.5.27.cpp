time_t
FwdState::timeLeft() const
{
    /* connection timeout */
    int ctimeout;
    if (serverDestinations[0]->getPeer()) {
        ctimeout = serverDestinations[0]->getPeer()->connect_timeout > 0 ?
                   serverDestinations[0]->getPeer()->connect_timeout : Config.Timeout.peer_connect;
    } else {
        ctimeout = Config.Timeout.connect;
    }

    /* calculate total forwarding timeout ??? */
    int ftimeout = Config.Timeout.forward - (squid_curtime - start_t);
    if (ftimeout < 0)
        ftimeout = 5;

    if (ftimeout < ctimeout)
        return (time_t)ftimeout;
    else
        return (time_t)ctimeout;
}