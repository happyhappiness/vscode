void
Ftp::Relay::processReplyBody()
{
    debugs(9, 3, status());

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        /*
         * probably was aborted because content length exceeds one
         * of the maximum size limits.
         */
        abortOnData("entry aborted after calling appendSuccessHeader()");
        return;
    }

    if (master().userDataDone) {
        // Squid-to-client data transfer done. Abort data transfer on our
        // side to allow new commands from ftp client
        abortOnData("Squid-to-client data connection is closed");
        return;
    }

#if USE_ADAPTATION

    if (adaptationAccessCheckPending) {
        debugs(9, 3, "returning due to adaptationAccessCheckPending");
        return;
    }

#endif

    if (data.readBuf != NULL && data.readBuf->hasContent()) {
        const mb_size_t csize = data.readBuf->contentSize();
        debugs(9, 5, "writing " << csize << " bytes to the reply");
        addVirginReplyBody(data.readBuf->content(), csize);
        data.readBuf->consume(csize);
    }

    entry->flush();

    maybeReadVirginBody();
}