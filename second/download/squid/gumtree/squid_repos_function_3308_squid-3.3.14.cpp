void
packerClean(Packer * p)
{
    assert(p);

    if (p->append == (append_f) store_append && p->real_handler)
        static_cast<StoreEntry*>(p->real_handler)->flush();

    /* it is not really necessary to do this, but, just in case... */
    p->append = NULL;
    p->packer_vprintf = NULL;
    p->real_handler = NULL;
}