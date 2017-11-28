void Adaptation::Icap::ModXact::encapsulateHead(MemBuf &icapBuf, const char *section, MemBuf &httpBuf, const HttpMsg *head)
{
    // update ICAP header
    icapBuf.Printf("%s=%d, ", section, (int) httpBuf.contentSize());

    // begin cloning
    HttpMsg::Pointer headClone;

    if (const HttpRequest* old_request = dynamic_cast<const HttpRequest*>(head)) {
        HttpRequest::Pointer new_request(new HttpRequest);
        Must(old_request->canonical);
        urlParse(old_request->method, old_request->canonical, new_request);
        new_request->http_ver = old_request->http_ver;
        headClone = new_request;
    } else if (const HttpReply *old_reply = dynamic_cast<const HttpReply*>(head)) {
        HttpReply::Pointer new_reply(new HttpReply);
        new_reply->sline = old_reply->sline;
        headClone = new_reply;
    }
    Must(headClone != NULL);
    headClone->inheritProperties(head);

    HttpHeaderPos pos = HttpHeaderInitPos;
    HttpHeaderEntry* p_head_entry = NULL;
    while (NULL != (p_head_entry = head->header.getEntry(&pos)) )
        headClone->header.addEntry(p_head_entry->clone());

    // end cloning

    // remove all hop-by-hop headers from the clone
    headClone->header.delById(HDR_PROXY_AUTHENTICATE);
    headClone->header.removeHopByHopEntries();

    // pack polished HTTP header
    packHead(httpBuf, headClone);

    // headClone unlocks and, hence, deletes the message we packed
}