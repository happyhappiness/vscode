clientStream_status_t
clientReplyContext::replyStatus()
{
    int done;
    /* Here because lower nodes don't need it */

    if (http->storeEntry() == NULL) {
        debugs(88, 5, "clientReplyStatus: no storeEntry");
        return STREAM_FAILED;	/* yuck, but what can we do? */
    }

    if (EBIT_TEST(http->storeEntry()->flags, ENTRY_ABORTED)) {
        /* TODO: Could upstream read errors (result.flags.error) be
         * lost, and result in undersize requests being considered
         * complete. Should we tcp reset such connections ?
         */
        debugs(88, 5, "clientReplyStatus: aborted storeEntry");
        return STREAM_FAILED;
    }

    if ((done = checkTransferDone()) != 0 || flags.complete) {
        debugs(88, 5, "clientReplyStatus: transfer is DONE");
        /* Ok we're finished, but how? */

        if (http->storeEntry()->getReply()->bodySize(http->request->method) < 0) {
            debugs(88, 5, "clientReplyStatus: closing, content_length < 0");
            return STREAM_FAILED;
        }

        if (!done) {
            debugs(88, 5, "clientReplyStatus: closing, !done, but read 0 bytes");
            return STREAM_FAILED;
        }

        if (!http->gotEnough()) {
            debugs(88, 5, "clientReplyStatus: client didn't get all it expected");
            return STREAM_UNPLANNED_COMPLETE;
        }

        if (http->request->flags.proxy_keepalive) {
            debugs(88, 5, "clientReplyStatus: stream complete and can keepalive");
            return STREAM_COMPLETE;
        }

        debugs(88, 5, "clientReplyStatus: stream was not expected to complete!");
        return STREAM_UNPLANNED_COMPLETE;
    }

    // XXX: Should this be checked earlier? We could return above w/o checking.
    if (reply->receivedBodyTooLarge(*http->request, http->out.offset - 4096)) {
        /* 4096 is a margin for the HTTP headers included in out.offset */
        debugs(88, 5, "clientReplyStatus: client reply body is too large");
        return STREAM_FAILED;
    }

    return STREAM_NONE;
}