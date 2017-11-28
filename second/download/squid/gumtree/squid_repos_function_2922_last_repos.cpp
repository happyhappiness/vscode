void
clientReplyContext::purgeRequest()
{
    debugs(88, 3, "Config2.onoff.enable_purge = " <<
           Config2.onoff.enable_purge);

    if (!Config2.onoff.enable_purge) {
        http->logType = LOG_TCP_DENIED;
        Ip::Address tmp_noaddr;
        tmp_noaddr.setNoAddr();
        ErrorState *err = clientBuildError(ERR_ACCESS_DENIED, Http::scForbidden, NULL,
                                           http->getConn() ? http->getConn()->clientConnection->remote : tmp_noaddr, http->request);
        startError(err);
        return;
    }

    /* Release both IP cache */
    ipcacheInvalidate(http->request->url.host());

    if (!http->flags.purging)
        purgeRequestFindObjectToPurge();
    else
        purgeDoMissPurge();
}