void
clientStreamCallback(clientStreamNode * thisObject, ClientHttpRequest * http,
                     HttpReply * rep, StoreIOBuffer replyBuffer)
{
    clientStreamNode *next;
    assert(thisObject && http && thisObject->node.next);
    next = thisObject->next();

    debugs(87, 3, "clientStreamCallback: Calling " << next->callback << " with cbdata " <<
           next->data.getRaw() << " from node " << thisObject);
    next->callback(next, http, rep, replyBuffer);
}