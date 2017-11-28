void
StoreEntry::replaceHttpReply(HttpReply *rep)
{
    debugs(20, 3, "StoreEntry::replaceHttpReply: " << url());
    Packer p;

    if (!mem_obj) {
        debugs(20, 0, "Attempt to replace object with no in-memory representation");
        return;
    }

    mem_obj->replaceHttpReply(rep);

    /* TODO: when we store headers serparately remove the header portion */
    /* TODO: mark the length of the headers ? */
    /* We ONLY want the headers */
    packerToStoreInit(&p, this);

    assert (isEmpty());

    getReply()->packHeadersInto(&p);

    rep->hdr_sz = mem_obj->endOffset();

    httpBodyPackInto(&getReply()->body, &p);

    packerClean(&p);
}