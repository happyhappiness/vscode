void
Ftp::Gateway::processReplyBody()
{
    debugs(9, 3, status());

    if (request->method == Http::METHOD_HEAD && (flags.isdir || theSize != -1)) {
        serverComplete();
        return;
    }

    /* Directory listings are special. They write ther own headers via the error objects */
    if (!flags.http_header_sent && data.readBuf->contentSize() >= 0 && !flags.isdir)
        appendSuccessHeader();

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        /*
         * probably was aborted because content length exceeds one
         * of the maximum size limits.
         */
        abortAll("entry aborted after calling appendSuccessHeader()");
        return;
    }

#if USE_ADAPTATION

    if (adaptationAccessCheckPending) {
        debugs(9, 3, "returning from Ftp::Gateway::processReplyBody due to adaptationAccessCheckPending");
        return;
    }

#endif

    if (flags.isdir) {
        if (!flags.listing) {
            flags.listing = 1;
            listing.reset();
        }
        parseListing();
        maybeReadVirginBody();
        return;
    } else if (const int csize = data.readBuf->contentSize()) {
        writeReplyBody(data.readBuf->content(), csize);
        debugs(9, 5, HERE << "consuming " << csize << " bytes of readBuf");
        data.readBuf->consume(csize);
    }

    entry->flush();

    maybeReadVirginBody();
}