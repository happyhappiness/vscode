int
clientReplyContext::storeNotOKTransferDone() const
{
    /*
     * Now, handle STORE_PENDING objects
     */
    MemObject *mem = http->storeEntry()->mem_obj;
    assert(mem != NULL);
    assert(http->request != NULL);
    /* mem->reply was wrong because it uses the UPSTREAM header length!!! */
    HttpReply const *curReply = mem->getReply();

    if (headers_sz == 0)
        /* haven't found end of headers yet */
        return 0;

    /*
     * Figure out how much data we are supposed to send.
     * If we are sending a body and we don't have a content-length,
     * then we must wait for the object to become STORE_OK.
     */
    if (curReply->content_length < 0)
        return 0;

    int64_t expectedLength = curReply->content_length + http->out.headers_sz;

    if (http->out.size < expectedLength)
        return 0;
    else {
        debugs(88,3,HERE << "storeNotOKTransferDone " <<
               " out.size=" << http->out.size <<
               " expectedLength=" << expectedLength);
        return 1;
    }
}