
    // CONNECT response was successfully parsed
    *status_ptr = rep.sline.status();

    // bail if we did not get an HTTP 200 (Connection Established) response
    if (rep.sline.status() != Http::scOkay) {
        server.logicError("unsupported CONNECT response status code");
        return;
    }

    if (rep.hdr_sz < connectRespBuf->contentSize()) {
        // preserve bytes that the server already sent after the CONNECT response
        server.len = connectRespBuf->contentSize() - rep.hdr_sz;
