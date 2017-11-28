bool
HttpStateData::continueAfterParsingHeader()
{
    if (flags.handling1xx) {
        debugs(11, 5, HERE << "wait for 1xx handling");
        Must(!flags.headers_parsed);
        return false;
    }

    if (!flags.headers_parsed && !eof) {
        debugs(11, 9, HERE << "needs more at " << readBuf->contentSize());
        flags.do_next_read = true;
        /** \retval false If we have not finished parsing the headers and may get more data.
         *                Schedules more reads to retrieve the missing data.
         */
        maybeReadVirginBody(); // schedules all kinds of reads; TODO: rename
        return false;
    }

    /** If we are done with parsing, check for errors */

    err_type error = ERR_NONE;

    if (flags.headers_parsed) { // parsed headers, possibly with errors
        // check for header parsing errors
        if (HttpReply *vrep = virginReply()) {
            const http_status s = vrep->sline.status;
            const HttpVersion &v = vrep->sline.version;
            if (s == HTTP_INVALID_HEADER && v != HttpVersion(0,9)) {
                debugs(11, DBG_IMPORTANT, "WARNING: HTTP: Invalid Response: Bad header encountered from " << entry->url() << " AKA " << request->GetHost() << request->urlpath.termedBuf() );
                error = ERR_INVALID_RESP;
            } else if (s == HTTP_HEADER_TOO_LARGE) {
                fwd->dontRetry(true);
                error = ERR_TOO_BIG;
            } else {
                return true; // done parsing, got reply, and no error
            }
        } else {
            // parsed headers but got no reply
            debugs(11, DBG_IMPORTANT, "WARNING: HTTP: Invalid Response: No reply at all for " << entry->url() << " AKA " << request->GetHost() << request->urlpath.termedBuf() );
            error = ERR_INVALID_RESP;
        }
    } else {
        assert(eof);
        if (readBuf->hasContent()) {
            error = ERR_INVALID_RESP;
            debugs(11, DBG_IMPORTANT, "WARNING: HTTP: Invalid Response: Headers did not parse at all for " << entry->url() << " AKA " << request->GetHost() << request->urlpath.termedBuf() );
        } else {
            error = ERR_ZERO_SIZE_OBJECT;
            debugs(11, (request->flags.accelerated?DBG_IMPORTANT:2), "WARNING: HTTP: Invalid Response: No object data received for " <<
                   entry->url() << " AKA " << request->GetHost() << request->urlpath.termedBuf() );
        }
    }

    assert(error != ERR_NONE);
    entry->reset();
    fwd->fail(new ErrorState(error, HTTP_BAD_GATEWAY, fwd->request));
    flags.do_next_read = false;
    serverConnection->close();
    return false; // quit on error
}