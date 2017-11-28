void Adaptation::Icap::ModXact::finalizeLogInfo()
{
    HttpRequest *adapted_request_ = nullptr;
    HttpReply *adapted_reply_ = nullptr;
    HttpRequest *virgin_request_ = const_cast<HttpRequest*>(&virginRequest());
    if (!(adapted_request_ = dynamic_cast<HttpRequest*>(adapted.header))) {
        // if the request was not adapted, use virgin request to simplify
        // the code further below
        adapted_request_ = virgin_request_;
        adapted_reply_ = dynamic_cast<HttpReply*>(adapted.header);
    }

    Adaptation::Icap::History::Pointer h = virgin_request_->icapHistory();
    Must(h != NULL); // ICAPXaction::maybeLog calls only if there is a log
    al.icp.opcode = ICP_INVALID;
    al.url = h->log_uri.termedBuf();
    const Adaptation::Icap::ServiceRep  &s = service();
    al.icap.reqMethod = s.cfg().method;

    al.cache.caddr = virgin_request_->client_addr;

    al.request = virgin_request_;
    HTTPMSGLOCK(al.request);
    al.adapted_request = adapted_request_;
    HTTPMSGLOCK(al.adapted_request);

    if (adapted_reply_) {
        al.reply = adapted_reply_;
        HTTPMSGLOCK(al.reply);
    } else
        al.reply = NULL;

    if (h->rfc931.size())
        al.cache.rfc931 = h->rfc931.termedBuf();

#if USE_OPENSSL
    if (h->ssluser.size())
        al.cache.ssluser = h->ssluser.termedBuf();
#endif
    al.cache.code = h->logType;

    const HttpMsg *virgin_msg = dynamic_cast<HttpReply*>(virgin.header);
    if (!virgin_msg)
        virgin_msg = virgin_request_;
    assert(virgin_msg != virgin.cause);
    al.http.clientRequestSz.header = virgin_msg->hdr_sz;
    if (virgin_msg->body_pipe != NULL)
        al.http.clientRequestSz.payloadData = virgin_msg->body_pipe->producedSize();

    // leave al.icap.bodyBytesRead negative if no body
    if (replyHttpHeaderSize >= 0 || replyHttpBodySize >= 0) {
        const int64_t zero = 0; // to make max() argument types the same
        const uint64_t headerSize = max(zero, replyHttpHeaderSize);
        const uint64_t bodySize =  max(zero, replyHttpBodySize);
        al.icap.bodyBytesRead = headerSize + bodySize;
        al.http.clientReplySz.header = headerSize;
        al.http.clientReplySz.payloadData = bodySize;
    }

    if (adapted_reply_) {
        al.http.code = adapted_reply_->sline.status();
        al.http.content_type = adapted_reply_->content_type.termedBuf();
        if (replyHttpBodySize >= 0)
            al.cache.highOffset = replyHttpBodySize;
        //don't set al.cache.objectSize because it hasn't exist yet

        MemBuf mb;
        mb.init();
        adapted_reply_->header.packInto(&mb);
        al.headers.reply = xstrdup(mb.buf);
        mb.clean();
    }
    prepareLogWithRequestDetails(adapted_request_, alep);
    Xaction::finalizeLogInfo();
}