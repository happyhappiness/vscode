bool
clientReplyContext::processConditional(StoreIOBuffer &result)
{
    StoreEntry *const e = http->storeEntry();

    if (e->getReply()->sline.status() != Http::scOkay) {
        debugs(88, 4, "Reply code " << e->getReply()->sline.status() << " != 200");
        http->logType = LOG_TCP_MISS;
        processMiss();
        return true;
    }

    HttpRequest &r = *http->request;

    if (r.header.has(HDR_IF_MATCH) && !e->hasIfMatchEtag(r)) {
        // RFC 2616: reply with 412 Precondition Failed if If-Match did not match
        sendPreconditionFailedError();
        return true;
    }

    if (r.header.has(HDR_IF_NONE_MATCH)) {
        // RFC 7232: If-None-Match recipient MUST ignore IMS
        r.flags.ims = false;
        r.ims = -1;
        r.imslen = 0;
        r.header.delById(HDR_IF_MODIFIED_SINCE);

        if (e->hasIfNoneMatchEtag(r)) {
            sendNotModifiedOrPreconditionFailedError();
            return true;
        }

        // None-Match is true (no ETag matched); treat as an unconditional hit
        return false;
    }

    if (r.flags.ims) {
        // handle If-Modified-Since requests from the client
        if (e->modifiedSince(r.ims, r.imslen)) {
            // Modified-Since is true; treat as an unconditional hit
            return false;

        } else {
            // otherwise reply with 304 Not Modified
            sendNotModified();
        }
        return true;
    }

    return false;
}