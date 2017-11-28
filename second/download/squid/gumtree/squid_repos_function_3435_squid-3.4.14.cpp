int
clientReplyContext::checkTransferDone()
{
    StoreEntry *entry = http->storeEntry();

    if (entry == NULL)
        return 0;

    /*
     * For now, 'done_copying' is used for special cases like
     * Range and HEAD requests.
     */
    if (http->flags.done_copying)
        return 1;

    if (http->request->flags.chunkedReply && !flags.complete) {
        // last-chunk was not sent
        return 0;
    }

    /*
     * Handle STORE_OK objects.
     * objectLen(entry) will be set proprely.
     * RC: Does objectLen(entry) include the Headers?
     * RC: Yes.
     */
    if (entry->store_status == STORE_OK) {
        return storeOKTransferDone();
    } else {
        return storeNotOKTransferDone();
    }
}