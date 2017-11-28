void
HttpStateData::processReplyHeader()
{
    /** Creates a blank header. If this routine is made incremental, this will not do */

    /* NP: all exit points to this function MUST call ctx_exit(ctx) */
    Ctx ctx = ctx_enter(entry->mem_obj->url);

    debugs(11, 3, "processReplyHeader: key '" << entry->getMD5Text() << "'");

    assert(!flags.headers_parsed);

    if (!readBuf->hasContent()) {
        ctx_exit(ctx);
        return;
    }

    http_status error = HTTP_STATUS_NONE;

    HttpReply *newrep = new HttpReply;
    const bool parsed = newrep->parse(readBuf, eof, &error);

    if (!parsed && readBuf->contentSize() > 5 && strncmp(readBuf->content(), "HTTP/", 5) != 0 && strncmp(readBuf->content(), "ICY", 3) != 0) {
        MemBuf *mb;
        HttpReply *tmprep = new HttpReply;
        tmprep->setHeaders(HTTP_OK, "Gatewaying", NULL, -1, -1, -1);
        tmprep->header.putExt("X-Transformed-From", "HTTP/0.9");
        mb = tmprep->pack();
        newrep->parse(mb, eof, &error);
        delete mb;
        delete tmprep;
    } else {
        if (!parsed && error > 0) { // unrecoverable parsing error
            debugs(11, 3, "processReplyHeader: Non-HTTP-compliant header: '" <<  readBuf->content() << "'");
            flags.headers_parsed = 1;
            newrep->sline.version = HttpVersion(1,0);
            newrep->sline.status = error;
            HttpReply *vrep = setVirginReply(newrep);
            entry->replaceHttpReply(vrep);
            ctx_exit(ctx);
            return;
        }

        if (!parsed) { // need more data
            assert(!error);
            assert(!eof);
            delete newrep;
            ctx_exit(ctx);
            return;
        }

        debugs(11, 9, "GOT HTTP REPLY HDR:\n---------\n" << readBuf->content() << "\n----------");

        header_bytes_read = headersEnd(readBuf->content(), readBuf->contentSize());
        readBuf->consume(header_bytes_read);
    }

    newrep->removeStaleWarnings();

    /* Skip 1xx messages for now. Advertised in Via as an internal 1.0 hop */
    if (newrep->sline.protocol == PROTO_HTTP && newrep->sline.status >= 100 && newrep->sline.status < 200) {

#if WHEN_HTTP11
        /* When HTTP/1.1 check if the client is expecting a 1xx reply and maybe pass it on */
        if (orig_request->header.has(HDR_EXPECT)) {
            // TODO: pass to the client anyway?
        }
#endif
        delete newrep;
        debugs(11, 2, HERE << "1xx headers consume " << header_bytes_read << " bytes header.");
        header_bytes_read = 0;
        if (reply_bytes_read > 0)
            debugs(11, 2, HERE << "1xx headers consume " << reply_bytes_read << " bytes reply.");
        reply_bytes_read = 0;
        ctx_exit(ctx);
        processReplyHeader();
        return;
    }

    flags.chunked = 0;
    if (newrep->sline.protocol == PROTO_HTTP && newrep->header.chunked()) {
        flags.chunked = 1;
        httpChunkDecoder = new ChunkedCodingParser;
    }

    if (!peerSupportsConnectionPinning())
        orig_request->flags.connection_auth_disabled = 1;

    HttpReply *vrep = setVirginReply(newrep);
    flags.headers_parsed = 1;

    keepaliveAccounting(vrep);

    checkDateSkew(vrep);

    processSurrogateControl (vrep);

    /** \todo IF the reply is a 1.0 reply, AND it has a Connection: Header
     * Parse the header and remove all referenced headers
     */

    orig_request->hier.peer_reply_status = newrep->sline.status;

    ctx_exit(ctx);
}