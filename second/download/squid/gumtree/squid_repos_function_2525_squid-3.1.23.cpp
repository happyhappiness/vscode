void
FtpStateData::start()
{
    if (!checkAuth(&request->header)) {
        /* create appropriate reply */
        HttpReply *reply = ftpAuthRequired(request, ftpRealm());
        entry->replaceHttpReply(reply);
        serverComplete();
        return;
    }

    checkUrlpath();
    buildTitleUrl();
    debugs(9, 5, HERE << "host=" << request->GetHost() << ", path=" <<
           request->urlpath << ", user=" << user << ", passwd=" <<
           password);

    state = BEGIN;
    ctrl.last_command = xstrdup("Connect to server");
    ctrl.buf = (char *)memAllocBuf(4096, &ctrl.size);
    ctrl.offset = 0;
    data.readBuf = new MemBuf;
    data.readBuf->init(4096, SQUID_TCP_SO_RCVBUF);
    scheduleReadControlReply(0);
}