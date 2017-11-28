void Adaptation::Icap::ModXact::finalizeLogInfo()
{
    HttpRequest * request_ = NULL;
    HttpReply * reply_ = NULL;
    if (!(request_ = dynamic_cast<HttpRequest*>(adapted.header))) {
        request_ = (virgin.cause? virgin.cause: dynamic_cast<HttpRequest*>(virgin.header));
        reply_ = dynamic_cast<HttpReply*>(adapted.header);
    }

    Adaptation::Icap::History::Pointer h = request_->icapHistory();
    Must(h != NULL); // ICAPXaction::maybeLog calls only if there is a log
    al.icp.opcode = ICP_INVALID;
    al.url = h->log_uri.termedBuf();
    const Adaptation::Icap::ServiceRep  &s = service();
    al.icap.reqMethod = s.cfg().method;

    al.cache.caddr = request_->client_addr;

    al.request = HTTPMSGLOCK(request_);
    if (reply_)
        al.reply = HTTPMSGLOCK(reply_);
    else
        al.reply = NULL;

    if (h->rfc931.size())
        al.cache.rfc931 = h->rfc931.termedBuf();

#if USE_SSL
    if (h->ssluser.size())
        al.cache.ssluser = h->ssluser.termedBuf();
#endif
    al.cache.code = h->logType;
    al.cache.requestSize = h->req_sz;
    if (reply_) {
        al.http.code = reply_->sline.status;
        al.http.content_type = reply_->content_type.termedBuf();
        al.cache.replySize = replyBodySize + reply_->hdr_sz;
        al.cache.highOffset = replyBodySize;
        //don't set al.cache.objectSize because it hasn't exist yet

        Packer p;
        MemBuf mb;

        mb.init();
        packerToMemInit(&p, &mb);

        reply_->header.packInto(&p);
        al.headers.reply = xstrdup(mb.buf);

        packerClean(&p);
        mb.clean();
    }
    prepareLogWithRequestDetails(request_, &al);
    Xaction::finalizeLogInfo();
}