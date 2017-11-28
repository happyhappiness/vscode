int
ConnectStateData::commRetryConnect()
{
    assert(addrcount > 0);

    if (addrcount == 1) {
        if (tries >= Config.retry.maxtries)
            return 0;

        if (squid_curtime - connstart > Config.Timeout.connect)
            return 0;
    } else {
        if (tries > addrcount) {
            /* Flush bad address count in case we are
             * skipping over incompatible protocol
             */
            ipcacheMarkAllGood(host);
            return 0;
        }
    }

    return commResetFD();
}