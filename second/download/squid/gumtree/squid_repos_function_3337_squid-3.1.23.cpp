void
clientReplyContext::traceReply(clientStreamNode * node)
{
    clientStreamNode *nextNode = (clientStreamNode *)node->node.next->data;
    StoreIOBuffer localTempBuffer;
    createStoreEntry(http->request->method, request_flags());
    localTempBuffer.offset = nextNode->readBuffer.offset + headers_sz;
    localTempBuffer.length = nextNode->readBuffer.length;
    localTempBuffer.data = nextNode->readBuffer.data;
    storeClientCopy(sc, http->storeEntry(),
                    localTempBuffer, SendMoreData, this);
    http->storeEntry()->releaseRequest();
    http->storeEntry()->buffer();
    HttpReply *rep = new HttpReply;
    rep->setHeaders(HTTP_OK, NULL, "text/plain", http->request->prefixLen(), 0, squid_curtime);
    http->storeEntry()->replaceHttpReply(rep);
    http->request->swapOut(http->storeEntry());
    http->storeEntry()->complete();
}