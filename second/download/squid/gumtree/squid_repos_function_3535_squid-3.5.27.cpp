void
clientStreamRead(clientStreamNode * thisObject, ClientHttpRequest * http,
                 StoreIOBuffer readBuffer)
{
    /* place the parameters on the 'stack' */
    clientStreamNode *prev;
    assert(thisObject && http && thisObject->prev());
    prev = thisObject->prev();

    debugs(87, 3, "clientStreamRead: Calling " << prev->readfunc <<
           " with cbdata " << prev->data.getRaw() << " from node " << thisObject);
    thisObject->readBuffer = readBuffer;
    prev->readfunc(prev, http);
}