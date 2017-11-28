void
clientStreamDetach(clientStreamNode * thisObject, ClientHttpRequest * http)
{
    clientStreamNode *temp = thisObject;

    assert(thisObject->node.next == NULL);
    debugs(87, 3, "clientStreamDetach: Detaching node " << thisObject);
    /* And clean up thisObject node */
    /* ESI TODO: push refcount class through to head */
    clientStreamNode *prev = NULL;

    if (thisObject->prev())
        prev = cbdataReference(thisObject->prev());

    thisObject->removeFromStream();

    cbdataReferenceDone(temp);

    delete thisObject;

    /* and tell the prev that the detach has occured */
    /*
     * We do it in thisObject order so that the detaching node is always
     * at the end of the list
     */

    if (prev) {
        debugs(87, 3, "clientStreamDetach: Calling " << prev->detach << " with cbdata " << prev->data.getRaw());

        if (cbdataReferenceValid(prev))
            prev->detach(prev, http);

        cbdataReferenceDone(prev);
    }
}