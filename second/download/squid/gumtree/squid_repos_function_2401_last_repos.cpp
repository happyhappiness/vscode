void
HttpRequest::swapOut(StoreEntry * e)
{
    assert(e);
    e->buffer();
    pack(e);
    e->flush();
}