void
Ftp::Gateway::processHeadResponse()
{
    debugs(9, 5, HERE << "handling HEAD response");
    ftpSendQuit(this);
    appendSuccessHeader();

    /*
     * On rare occasions I'm seeing the entry get aborted after
     * readControlReply() and before here, probably when
     * trying to write to the client.
     */
    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        abortAll("entry aborted while processing HEAD");
        return;
    }

#if USE_ADAPTATION
    if (adaptationAccessCheckPending) {
        debugs(9,3, HERE << "returning due to adaptationAccessCheckPending");
        return;
    }
#endif

    // processReplyBody calls serverComplete() since there is no body
    processReplyBody();
}