void
Ftp::Gateway::appendSuccessHeader()
{
    debugs(9, 3, HERE);

    if (flags.http_header_sent)
        return;

    HttpReply *reply = new HttpReply;

    flags.http_header_sent = 1;

    assert(entry->isEmpty());

    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);

    entry->buffer();    /* released when done processing current data payload */

    SBuf urlPath = request->url.path();
    auto t = urlPath.rfind('/');
    SBuf filename = urlPath.substr(t != SBuf::npos ? t : 0);

    const char *mime_type = NULL;
    const char *mime_enc = NULL;

    if (flags.isdir) {
        mime_type = "text/html";
    } else {
        switch (typecode) {

        case 'I':
            mime_type = "application/octet-stream";
            // XXX: performance regression, c_str() may reallocate
            mime_enc = mimeGetContentEncoding(filename.c_str());
            break;

        case 'A':
            mime_type = "text/plain";
            break;

        default:
            // XXX: performance regression, c_str() may reallocate
            mime_type = mimeGetContentType(filename.c_str());
            mime_enc = mimeGetContentEncoding(filename.c_str());
            break;
        }
    }

    /* set standard stuff */

    if (0 == getCurrentOffset()) {
        /* Full reply */
        reply->setHeaders(Http::scOkay, "Gatewaying", mime_type, theSize, mdtm, -2);
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
        reply->setHeaders(Http::scOkay, "Gatewaying", mime_type, theSize, mdtm, -2);
    } else {
        /* Partial reply */
        HttpHdrRangeSpec range_spec;
        range_spec.offset = getCurrentOffset();
        range_spec.length = theSize - getCurrentOffset();
        reply->setHeaders(Http::scPartialContent, "Gatewaying", mime_type, theSize - getCurrentOffset(), mdtm, -2);
        httpHeaderAddContRange(&reply->header, range_spec, theSize);
    }

    /* additional info */
    if (mime_enc)
        reply->header.putStr(Http::HdrType::CONTENT_ENCODING, mime_enc);

    reply->sources |= HttpMsg::srcFtp;
    setVirginReply(reply);
    adaptOrFinalizeReply();
}