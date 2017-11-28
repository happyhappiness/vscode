bool
HttpHeader::getList(Http::HdrType id, String *s) const
{
    debugs(55, 9, this << " joining for id " << id);
    /* only fields from ListHeaders array can be "listed" */
    assert(Http::HeaderLookupTable.lookup(id).list);

    if (!CBIT_TEST(mask, id))
        return false;

    for (auto e: entries) {
        if (e && e->id == id)
            strListAdd(s, e->value.termedBuf(), ',');
    }

    /*
     * note: we might get an empty (size==0) string if there was an "empty"
     * header. This results in an empty length String, which may have a NULL
     * buffer.
     */
    /* temporary warning: remove it? (Is it useful for diagnostics ?) */
    if (!s->size())
        debugs(55, 3, "empty list header: " << Http::HeaderLookupTable.lookup(id).name << "(" << id << ")");
    else
        debugs(55, 6, this << ": joined for id " << id << ": " << s);

    return true;
}