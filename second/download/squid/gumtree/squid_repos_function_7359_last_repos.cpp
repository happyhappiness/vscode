void
Mgr::Inquirer::start()
{
    debugs(16, 5, HERE);
    Ipc::Inquirer::start();
    Must(Comm::IsConnOpen(conn));
    Must(aggrAction != NULL);

    std::unique_ptr<MemBuf> replyBuf;
    if (strands.empty()) {
        LOCAL_ARRAY(char, url, MAX_URL);
        snprintf(url, MAX_URL, "%s", aggrAction->command().params.httpUri.termedBuf());
        const MasterXaction::Pointer mx = new MasterXaction(XactionInitiator::initIpc);
        HttpRequest *req = HttpRequest::FromUrl(url, mx);
        ErrorState err(ERR_INVALID_URL, Http::scNotFound, req);
        std::unique_ptr<HttpReply> reply(err.BuildHttpReply());
        replyBuf.reset(reply->pack());
    } else {
        std::unique_ptr<HttpReply> reply(new HttpReply);
        reply->setHeaders(Http::scOkay, NULL, "text/plain", -1, squid_curtime, squid_curtime);
        reply->header.putStr(Http::HdrType::CONNECTION, "close"); // until we chunk response
        replyBuf.reset(reply->pack());
    }
    writer = asyncCall(16, 5, "Mgr::Inquirer::noteWroteHeader",
                       CommCbMemFunT<Inquirer, CommIoCbParams>(this, &Inquirer::noteWroteHeader));
    Comm::Write(conn, replyBuf.get(), writer);
}