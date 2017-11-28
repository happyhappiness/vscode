void
HttpRequest::swapOut(StoreEntry * e)
{
    Packer p;
    assert(e);
    packerToStoreInit(&p, e);
    pack(&p);
    packerClean(&p);
}