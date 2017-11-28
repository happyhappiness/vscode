void Adaptation::Icap::ModXact::packHead(MemBuf &httpBuf, const HttpMsg *head)
{
    Packer p;
    packerToMemInit(&p, &httpBuf);
    head->packInto(&p, true);
    packerClean(&p);
}