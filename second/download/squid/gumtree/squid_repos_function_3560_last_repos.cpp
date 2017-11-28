void Adaptation::Icap::ModXact::encapsulateHead(MemBuf &icapBuf, const char *section, MemBuf &httpBuf, const HttpMsg *head)
{
    // update ICAP header
    icapBuf.appendf("%s=%d, ", section, (int) httpBuf.contentSize());

    // begin cloning
    HttpMsg::Pointer headClone;

    if (const HttpRequest* old_request = dynamic_cast<const HttpRequest*>(head)) {
        HttpRequest::Pointer new_request(new HttpRequest(old_request->masterXaction));
        // copy the requst-line details
        new_request->method = old_request->method;
        new_request->url = old_request->url;
        new_request->http_ver = old_request->http_ver;
        headClone = new_request.getRaw();
    } else if (const HttpReply *old_reply = dynamic_cast<const HttpReply*>(head)) {
        HttpReply::Pointer new_reply(new HttpReply);
        new_reply->sline = old_reply->sline;
        headClone = new_reply.getRaw();
    }
    Must(headClone);
    headClone->inheritProperties(head);

    HttpHeaderPos pos = HttpHeaderInitPos;
    while (HttpHeaderEntry* p_head_entry = head->header.getEntry(&pos))
        headClone->header.addEntry(p_head_entry->clone());

    // end cloning

    // remove all hop-by-hop headers from the clone
    headClone->header.delById(Http::HdrType::PROXY_AUTHENTICATE);
    headClone->header.removeHopByHopEntries();

    // pack polished HTTP header
    packHead(httpBuf, headClone.getRaw());

    // headClone unlocks and, hence, deletes the message we packed
}