static void
clientProcessRequestFinished(ConnStateData *conn, const HttpRequest::Pointer &request)
{
    /*
     * DPW 2007-05-18
     * Moved the TCP_RESET feature from clientReplyContext::sendMoreData
     * to here because calling comm_reset_close() causes http to
     * be freed and the above connNoteUseOfBuffer() would hit an
     * assertion, not to mention that we were accessing freed memory.
     */
    if (request != NULL && request->flags.resetTcp && Comm::IsConnOpen(conn->clientConnection)) {
        debugs(33, 3, HERE << "Sending TCP RST on " << conn->clientConnection);
        conn->flags.readMore = false;
        comm_reset_close(conn->clientConnection);
    }
}