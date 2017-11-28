clientStream_status_t
clientStreamStatus(clientStreamNode * thisObject, ClientHttpRequest * http)
{
    clientStreamNode *prev;
    assert(thisObject && http && thisObject->node.prev);
    prev = (clientStreamNode *)thisObject->node.prev->data;
    return prev->status(prev, http);
}