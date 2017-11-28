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
            flags.headers_parsed = true;
            newrep->sline.version = HttpVersion(1,1);
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

        debugs(11, 2, "HTTP Server " << serverConnection);
        debugs(11, 2, "HTTP Server REPLY:\n---------\n" << readBuf->content() << "\n----------");

        header_bytes_read = headersEnd(readBuf->content(), readBuf->contentSize());
        readBuf->consume(header_bytes_read);
    }

    newrep->removeStaleWarnings();

    if (newrep->sline.protocol == AnyP::PROTO_HTTP && newrep->sline.status >= 100 && newrep->sline.status < 200) {
        handle1xx(newrep);
        ctx_exit(ctx);
        return;
    }

    flags.chunked = false;
    if (newrep->sline.protocol == AnyP::PROTO_HTTP && newrep->header.chunked()) {
        flags.chunked = true;
        httpChunkDecoder = new ChunkedCodingParser;
    }

    if (!peerSupportsConnectionPinning())
        request->flags.connectionAuthDisabled = 1;

    HttpReply *vrep = setVirginReply(newrep);
    flags.headers_parsed = true;

    keepaliveAccounting(vrep);

    checkDateSkew(vrep);

    processSurrogateControl (vrep);

    request->hier.peer_reply_status = newrep->sline.status;

    ctx_exit(ctx);
}