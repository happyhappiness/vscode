void
clientStreamInit(dlink_list * list, CSR * func, CSD * rdetach, CSS * readstatus,
                 ClientStreamData readdata, CSCB * callback, CSD * cdetach, ClientStreamData callbackdata,
                 StoreIOBuffer tailBuffer)
{
    clientStreamNode *temp = new clientStreamNode(func, NULL, rdetach, readstatus, readdata);
    dlinkAdd(cbdataReference(temp), &temp->node, list);
    temp->head = list;
    clientStreamInsertHead(list, NULL, callback, cdetach, NULL, callbackdata);
    temp = (clientStreamNode *)list->tail->data;
    temp->readBuffer = tailBuffer;
}