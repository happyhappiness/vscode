void
HttpStateData::handleMoreRequestBodyAvailable()
{
    if (eof || fd < 0) {
        // XXX: we should check this condition in other callbacks then!
        // TODO: Check whether this can actually happen: We should unsubscribe
        // as a body consumer when the above condition(s) are detected.
        debugs(11, 1, HERE << "Transaction aborted while reading HTTP body");
        return;
    }

    assert(requestBodySource != NULL);

    if (requestBodySource->buf().hasContent()) {
        // XXX: why does not this trigger a debug message on every request?

        if (flags.headers_parsed && !flags.abuse_detected) {
            flags.abuse_detected = 1;
            debugs(11, 1, "http handleMoreRequestBodyAvailable: Likely proxy abuse detected '" << orig_request->client_addr << "' -> '" << entry->url() << "'" );

            if (virginReply()->sline.status == HTTP_INVALID_HEADER) {
                comm_close(fd);
                return;
            }
        }
    }

    HttpStateData::handleMoreRequestBodyAvailable();
}