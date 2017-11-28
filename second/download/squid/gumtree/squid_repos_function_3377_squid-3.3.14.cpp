void
clientReplyContext::handleIMSReply(StoreIOBuffer result)
{
    if (deleting)
        return;

    debugs(88, 3, "handleIMSReply: " << http->storeEntry()->url() << ", " << (long unsigned) result.length << " bytes" );

    if (http->storeEntry() == NULL)
        return;

    if (result.flags.error && !EBIT_TEST(http->storeEntry()->flags, ENTRY_ABORTED))
        return;

    /* update size of the request */
    reqsize = result.length + reqofs;

    const http_status status = http->storeEntry()->getReply()->sline.status;

    // request to origin was aborted
    if (EBIT_TEST(http->storeEntry()->flags, ENTRY_ABORTED)) {
        debugs(88, 3, "handleIMSReply: request to origin aborted '" << http->storeEntry()->url() << "', sending old entry to client" );
        http->logType = LOG_TCP_REFRESH_FAIL_OLD;
        sendClientOldEntry();
    }

    HttpReply *old_rep = (HttpReply *) old_entry->getReply();

    // origin replied 304
    if (status == HTTP_NOT_MODIFIED) {
        http->logType = LOG_TCP_REFRESH_UNMODIFIED;
        http->request->flags.staleIfHit = 0; // old_entry is no longer stale

        // update headers on existing entry
        old_rep->updateOnNotModified(http->storeEntry()->getReply());
        old_entry->timestampsSet();

        // if client sent IMS

        if (http->request->flags.ims && !old_entry->modifiedSince(http->request)) {
            // forward the 304 from origin
            debugs(88, 3, "handleIMSReply: origin replied 304, revalidating existing entry and forwarding 304 to client");
            sendClientUpstreamResponse();
        } else {
            // send existing entry, it's still valid
            debugs(88, 3, "handleIMSReply: origin replied 304, revalidating existing entry and sending " <<
                   old_rep->sline.status << " to client");
            sendClientOldEntry();
        }
    }

    // origin replied with a non-error code
    else if (status > HTTP_STATUS_NONE && status < HTTP_INTERNAL_SERVER_ERROR) {
        // forward response from origin
        http->logType = LOG_TCP_REFRESH_MODIFIED;
        debugs(88, 3, "handleIMSReply: origin replied " << status << ", replacing existing entry and forwarding to client");
        sendClientUpstreamResponse();
    }

    // origin replied with an error
    else if (http->request->flags.failOnValidationError) {
        http->logType = LOG_TCP_REFRESH_FAIL_ERR;
        debugs(88, 3, "handleIMSReply: origin replied with error " << status <<
               ", forwarding to client due to fail_on_validation_err");
        sendClientUpstreamResponse();
    } else {
        // ignore and let client have old entry
        http->logType = LOG_TCP_REFRESH_FAIL_OLD;
        debugs(88, 3, "handleIMSReply: origin replied with error " <<
               status << ", sending old entry (" << old_rep->sline.status << ") to client");
        sendClientOldEntry();
    }
}