bool
StoreEntry::hasEtag(ETag &etag) const
{
    if (const HttpReply *reply = getReply()) {
        etag = reply->header.getETag(Http::HdrType::ETAG);
        if (etag.str)
            return true;
    }
    return false;
}