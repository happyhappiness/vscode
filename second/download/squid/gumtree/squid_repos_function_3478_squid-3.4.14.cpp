clientStreamNode *
clientStreamNew(CSR * readfunc, CSCB * callback, CSD * detach, CSS * status,
                ClientStreamData data)
{
    clientStreamNode *temp;
    CBDATA_INIT_TYPE_FREECB(clientStreamNode, clientStreamFree);
    temp = cbdataAlloc(clientStreamNode);
    temp->readfunc = readfunc;
    temp->callback = callback;
    temp->detach = detach;
    temp->status = status;
    temp->data = data;
    return temp;
}