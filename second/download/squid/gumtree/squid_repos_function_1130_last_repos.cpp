static void
downloaderRecipient(clientStreamNode * node, ClientHttpRequest * http,
                    HttpReply * rep, StoreIOBuffer receivedData)
{
    debugs(33, 6, MYNAME);
    /* Test preconditions */
    assert(node);

    /* TODO: handle this rather than asserting
     * - it should only ever happen if we cause an abort and
     * the callback chain loops back to here, so we can simply return.
     * However, that itself shouldn't happen, so it stays as an assert for now.
     */
    assert(cbdataReferenceValid(node));
    assert(!node->node.next);
    DownloaderContext::Pointer context = dynamic_cast<DownloaderContext *>(node->data.getRaw());
    assert(context);

    if (context->downloader.valid())
        context->downloader->handleReply(node, http, rep, receivedData);
}