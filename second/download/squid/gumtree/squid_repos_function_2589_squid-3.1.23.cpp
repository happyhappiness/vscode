void
FtpStateData::appendSuccessHeader()
{
    const char *mime_type = NULL;
    const char *mime_enc = NULL;
    String urlpath = request->urlpath;
    const char *filename = NULL;
    const char *t = NULL;
    StoreEntry *e = entry;

    debugs(9, 3, HERE);

    if (flags.http_header_sent)
        return;

    HttpReply *reply = new HttpReply;

    flags.http_header_sent = 1;

    assert(e->isEmpty());

    EBIT_CLR(e->flags, ENTRY_FWD_HDR_WAIT);

    e->buffer();	/* released when done processing current data payload */

    filename = (t = urlpath.rpos('/')) ? t + 1 : urlpath.termedBuf();

    if (flags.isdir) {
        mime_type = "text/html";
    } else {
        switch (typecode) {

        case 'I':
            mime_type = "application/octet-stream";
            mime_enc = mimeGetContentEncoding(filename);
            break;

        case 'A':
            mime_type = "text/plain";
            break;

        default:
            mime_type = mimeGetContentType(filename);
            mime_enc = mimeGetContentEncoding(filename);
            break;
        }
    }

    /* set standard stuff */

    if (0 == getCurrentOffset()) {
        /* Full reply */
        reply->setHeaders(HTTP_OK, "Gatewaying", mime_type, theSize, mdtm, -2);
    } else if (theSize < getCurrentOffset()) {
        /*
         * DPW 2007-05-04
         * offset should not be larger than theSize.  We should
         * not be seeing this condition any more because we'll only
         * send REST if we know the theSize and if it is less than theSize.
         */
        debugs(0,DBG_CRITICAL,HERE << "Whoops! " <<
               " current offset=" << getCurrentOffset() <<
               ", but theSize=" << theSize <<
               ".  assuming full content response");
        reply->setHeaders(HTTP_OK, "Gatewaying", mime_type, theSize, mdtm, -2);
    } else {
        /* Partial reply */
        HttpHdrRangeSpec range_spec;
        range_spec.offset = getCurrentOffset();
        range_spec.length = theSize - getCurrentOffset();
        reply->setHeaders(HTTP_PARTIAL_CONTENT, "Gatewaying", mime_type, theSize - getCurrentOffset(), mdtm, -2);
        httpHeaderAddContRange(&reply->header, range_spec, theSize);
    }

    /* additional info */
    if (mime_enc)
        reply->header.putStr(HDR_CONTENT_ENCODING, mime_enc);

    setVirginReply(reply);
    adaptOrFinalizeReply();
}