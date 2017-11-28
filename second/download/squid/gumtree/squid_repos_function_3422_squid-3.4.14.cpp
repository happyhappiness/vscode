void
clientReplyContext::processConditional(StoreIOBuffer &result)
{
    StoreEntry *const e = http->storeEntry();

    if (e->getReply()->sline.status() != Http::scOkay) {
        debugs(88, 4, "clientReplyContext::processConditional: Reply code " <<
               e->getReply()->sline.status() << " != 200");
        http->logType = LOG_TCP_MISS;
        processMiss();
        return;
    }

    HttpRequest &r = *http->request;

    if (r.header.has(HDR_IF_MATCH) && !e->hasIfMatchEtag(r)) {
        // RFC 2616: reply with 412 Precondition Failed if If-Match did not match
        sendPreconditionFailedError();
        return;
    }

    bool matchedIfNoneMatch = false;
    if (r.header.has(HDR_IF_NONE_MATCH)) {
        if (!e->hasIfNoneMatchEtag(r)) {
            // RFC 2616: ignore IMS if If-None-Match did not match
            r.flags.ims = false;
            r.ims = -1;
            r.imslen = 0;
            r.header.delById(HDR_IF_MODIFIED_SINCE);
            http->logType = LOG_TCP_MISS;
            sendMoreData(result);
            return;
        }

        if (!r.flags.ims) {
            // RFC 2616: if If-None-Match matched and there is no IMS,
            // reply with 304 Not Modified or 412 Precondition Failed
            sendNotModifiedOrPreconditionFailedError();
            return;
        }

        // otherwise check IMS below to decide if we reply with 304 or 412
        matchedIfNoneMatch = true;
    }

    if (r.flags.ims) {
        // handle If-Modified-Since requests from the client
        if (e->modifiedSince(&r)) {
            http->logType = LOG_TCP_IMS_HIT;
            sendMoreData(result);
            return;
        }

        if (matchedIfNoneMatch) {
            // If-None-Match matched, reply with 304 Not Modified or
            // 412 Precondition Failed
            sendNotModifiedOrPreconditionFailedError();
            return;
        }

        // otherwise reply with 304 Not Modified
        sendNotModified();
    }
}