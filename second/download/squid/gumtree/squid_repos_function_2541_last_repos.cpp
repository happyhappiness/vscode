void
StoreEntry::startWriting()
{
    /* TODO: when we store headers separately remove the header portion */
    /* TODO: mark the length of the headers ? */
    /* We ONLY want the headers */

    assert (isEmpty());
    assert(mem_obj);

    const HttpReply *rep = getReply();
    assert(rep);

    buffer();
    rep->packHeadersInto(this);
    mem_obj->markEndOfReplyHeaders();
    EBIT_CLR(flags, ENTRY_FWD_HDR_WAIT);

    rep->body.packInto(this);
    flush();
}