bool
StoreEntry::hasEtag(ETag &etag) const
{
    if (const HttpReply *reply = getReply()) {
        etag = reply->header.getETag(HDR_ETAG);
        if (etag.str)
            return true;
    }
    return false;
}