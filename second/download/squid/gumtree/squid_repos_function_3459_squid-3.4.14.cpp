void
clientReplyContext::processReplyAccess ()
{
    /* NP: this should probably soft-fail to a zero-sized-reply error ?? */
    assert(reply);

    /** Don't block our own responses or HTTP status messages */
    if (http->logType == LOG_TCP_DENIED ||
            http->logType == LOG_TCP_DENIED_REPLY ||
            alwaysAllowResponse(reply->sline.status())) {
        headers_sz = reply->hdr_sz;
        processReplyAccessResult(ACCESS_ALLOWED);
        return;
    }

    /** Check for reply to big error */
    if (reply->expectedBodyTooLarge(*http->request)) {
        sendBodyTooLargeError();
        return;
    }

    headers_sz = reply->hdr_sz;

    /** check for absent access controls (permit by default) */
    if (!Config.accessList.reply) {
        processReplyAccessResult(ACCESS_ALLOWED);
        return;
    }

    /** Process http_reply_access lists */
    ACLFilledChecklist *replyChecklist =
        clientAclChecklistCreate(Config.accessList.reply, http);
    replyChecklist->reply = reply;
    HTTPMSGLOCK(replyChecklist->reply);
    replyChecklist->nonBlockingCheck(ProcessReplyAccessResult, this);
}