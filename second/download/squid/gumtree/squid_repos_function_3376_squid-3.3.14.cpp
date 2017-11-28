void
clientReplyContext::sendClientOldEntry()
{
    /* Get the old request back */
    restoreState();
    /* here the data to send is in the next nodes buffers already */
    assert(!EBIT_TEST(http->storeEntry()->flags, ENTRY_ABORTED));
    /* sendMoreData tracks the offset as well.
     * Force it back to zero */
    reqofs = 0;
    StoreIOBuffer tempresult (reqsize, reqofs, next()->readBuffer.data);
    sendMoreData(tempresult);
}