bool
StoreEntry::validLength() const
{
    int64_t diff;
    const HttpReply *reply;
    assert(mem_obj != NULL);
    reply = getReply();
    debugs(20, 3, "storeEntryValidLength: Checking '" << getMD5Text() << "'");
    debugs(20, 5, "storeEntryValidLength:     object_len = " <<
           objectLen());
    debugs(20, 5, "storeEntryValidLength:         hdr_sz = " << reply->hdr_sz);
    debugs(20, 5, "storeEntryValidLength: content_length = " << reply->content_length);

    if (reply->content_length < 0) {
        debugs(20, 5, "storeEntryValidLength: Unspecified content length: " << getMD5Text());
        return 1;
    }

    if (reply->hdr_sz == 0) {
        debugs(20, 5, "storeEntryValidLength: Zero header size: " << getMD5Text());
        return 1;
    }

    if (mem_obj->method == Http::METHOD_HEAD) {
        debugs(20, 5, "storeEntryValidLength: HEAD request: " << getMD5Text());
        return 1;
    }

    if (reply->sline.status() == Http::scNotModified)
        return 1;

    if (reply->sline.status() == Http::scNoContent)
        return 1;

    diff = reply->hdr_sz + reply->content_length - objectLen();

    if (diff == 0)
        return 1;

    debugs(20, 3, "storeEntryValidLength: " << (diff < 0 ? -diff : diff)  << " bytes too " << (diff < 0 ? "big" : "small") <<"; '" << getMD5Text() << "'" );

    return 0;
}