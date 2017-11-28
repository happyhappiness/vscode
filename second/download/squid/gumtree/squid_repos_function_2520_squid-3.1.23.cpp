void
FtpStateData::processReplyBody()
{
    debugs(9, 3, HERE << "FtpStateData::processReplyBody starting.");

    if (request->method == METHOD_HEAD && (flags.isdir || theSize != -1)) {
        serverComplete();
        return;
    }

    if (!flags.http_header_sent && data.readBuf->contentSize() >= 0)
        appendSuccessHeader();

    if (EBIT_TEST(entry->flags, ENTRY_ABORTED)) {
        /*
         * probably was aborted because content length exceeds one
         * of the maximum size limits.
         */
        abortTransaction("entry aborted after calling appendSuccessHeader()");
        return;
    }

#if USE_ADAPTATION

    if (adaptationAccessCheckPending) {
        debugs(9,3, HERE << "returning from FtpStateData::processReplyBody due to adaptationAccessCheckPending");
        return;
    }

#endif

    if (flags.isdir && !flags.listing_started)
        listingStart();

    if (flags.isdir) {
        parseListing();
    } else if (const int csize = data.readBuf->contentSize()) {
        writeReplyBody(data.readBuf->content(), csize);
        debugs(9, 5, HERE << "consuming " << csize << " bytes of readBuf");
        data.readBuf->consume(csize);
    }

    entry->flush();

    maybeReadVirginBody();
}