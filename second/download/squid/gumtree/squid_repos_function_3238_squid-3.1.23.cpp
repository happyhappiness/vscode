void
packerToStoreInit(Packer * p, StoreEntry * e)
{
    assert(p && e);
    p->append = (append_f) store_append;
    p->packer_vprintf = (vprintf_f) store_vprintf;
    p->real_handler = e;
    e->buffer();
}