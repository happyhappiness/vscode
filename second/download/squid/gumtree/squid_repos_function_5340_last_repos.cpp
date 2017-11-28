void
Ftp::Gateway::start()
{
    if (!checkAuth(&request->header)) {
        /* create appropriate reply */
        SBuf realm(ftpRealm()); // local copy so SBuf wont disappear too early
        HttpReply *reply = ftpAuthRequired(request, realm);
        entry->replaceHttpReply(reply);
        serverComplete();
        return;
    }

    checkUrlpath();
    buildTitleUrl();
    debugs(9, 5, "FD " << (ctrl.conn ? ctrl.conn->fd : -1) << " : host=" << request->url.host() <<
           ", path=" << request->url.path() << ", user=" << user << ", passwd=" << password);
    state = BEGIN;
    Ftp::Client::start();
}