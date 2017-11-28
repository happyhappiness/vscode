void
clientStreamAbort(clientStreamNode * thisObject, ClientHttpRequest * http)
{
    dlink_list *list;

    assert(thisObject != NULL);
    assert(http != NULL);
    list = thisObject->head;
    debugs(87, 3, "clientStreamAbort: Aborting stream with tail " << list->tail);

    if (list->tail) {
        clientStreamDetach((clientStreamNode *)list->tail->data, http);
    }
}