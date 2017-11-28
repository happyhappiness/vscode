void
ESIContext::fail ()
{
    debugs(86, 5, "ESIContext::fail: this=" << this);
    /* check preconditions */
    assert (pos == 0);
    /* cleanup current state */
    freeResources ();
    /* Stop altering thisNode request */
    flags.oktosend = 1;
    flags.finished = 1;
    /* don't honour range requests - for errors we send it all */
    flags.error = 1;
    /* create an error object */
    ErrorState * err = clientBuildError(errorpage, errorstatus, NULL, http->getConn()->peer, http->request);
    err->err_msg = errormessage;
    errormessage = NULL;
    rep = err->BuildHttpReply();
    assert (rep->body.mb->contentSize() >= 0);
    size_t errorprogress = rep->body.mb->contentSize();
    /* Tell esiSend where to start sending from */
    outbound_offset = 0;
    /* copy the membuf from the reply to outbound */

    while (errorprogress < (size_t)rep->body.mb->contentSize()) {
        appendOutboundData(new ESISegment);
        errorprogress += outboundtail->append(rep->body.mb->content() + errorprogress, rep->body.mb->contentSize() - errorprogress);
    }

    /* the esiCode now thinks that the error is the outbound,
     * and all processing has finished. */
    /* Send as much as we can */
    send ();

    /* don't cancel anything. The stream nodes will clean up after
     * themselves when the reply is freed - and we don't know what to
     * clean anyway.
     */
}