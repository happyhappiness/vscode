void
clientStreamInsertHead(dlink_list * list, CSR * func, CSCB * callback,
                       CSD * detach, CSS * status, ClientStreamData data)
{

    /* test preconditions */
    assert(list != NULL);
    assert(list->head);
    clientStreamNode *temp = clientStreamNew(func, callback, detach, status, data);
    temp->head = list;
    debugs(87, 3, "clientStreamInsertHead: Inserted node " << temp <<
           " with data " << data.getRaw() << " after head");

    if (list->head->next)
        temp->readBuffer = ((clientStreamNode *)list->head->next->data)->readBuffer;

    dlinkAddAfter(cbdataReference(temp), &temp->node, list->head, list);
}