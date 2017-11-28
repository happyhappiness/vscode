HttpStateData::ConnectionStatus
HttpStateData::persistentConnStatus() const
{
    debugs(11, 3, "persistentConnStatus: FD " << fd << " eof=" << eof);
    if (eof) // already reached EOF
        return COMPLETE_NONPERSISTENT_MSG;

    /* If server fd is closing (but we have not been notified yet), stop Comm
       I/O to avoid assertions. TODO: Change Comm API to handle callers that
       want more I/O after async closing (usually initiated by others). */
    // XXX: add canReceive or s/canSend/canTalkToServer/
    if (!canSend(fd))
        return COMPLETE_NONPERSISTENT_MSG;

    /** \par
     * In chunked response we do not know the content length but we are absolutely
     * sure about the end of response, so we are calling the statusIfComplete to
     * decide if we can be persistant
     */
    if (lastChunk && flags.chunked)
        return statusIfComplete();

    const HttpReply *vrep = virginReply();
    debugs(11, 5, "persistentConnStatus: content_length=" << vrep->content_length);

    const int64_t clen = vrep->bodySize(request->method);

    debugs(11, 5, "persistentConnStatus: clen=" << clen);

    /* If the body size is unknown we must wait for EOF */
    if (clen < 0)
        return INCOMPLETE_MSG;

    /** \par
     * If the body size is known, we must wait until we've gotten all of it. */
    if (clen > 0) {
        // old technique:
        // if (entry->mem_obj->endOffset() < vrep->content_length + vrep->hdr_sz)
        const int64_t body_bytes_read = reply_bytes_read - header_bytes_read;
        debugs(11,5, "persistentConnStatus: body_bytes_read=" <<
               body_bytes_read << " content_length=" << vrep->content_length);

        if (body_bytes_read < vrep->content_length)
            return INCOMPLETE_MSG;

        if (body_bytes_truncated > 0) // already read more than needed
            return COMPLETE_NONPERSISTENT_MSG; // disable pconns
    }

    /** \par
     * If there is no message body or we got it all, we can be persistent */
    return statusIfComplete();
}