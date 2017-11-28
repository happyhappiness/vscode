void Adaptation::Icap::ModXact::packHead(MemBuf &httpBuf, const HttpMsg *head)
{
    head->packInto(&httpBuf, true);
}