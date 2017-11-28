void
StoreEntry::startWriting()
{
    Packer p;

    /* TODO: when we store headers serparately remove the header portion */
    /* TODO: mark the length of the headers ? */
    /* We ONLY want the headers */
    packerToStoreInit(&p, this);

    assert (isEmpty());
    assert(mem_obj);

    const HttpReply *rep = getReply();
    assert(rep);

    rep->packHeadersInto(&p);
    mem_obj->markEndOfReplyHeaders();

    rep->body.packInto(&p);

    packerClean(&p);
}