bool
HttpHeader::needUpdate(HttpHeader const *fresh) const
{
    for (unsigned int i = 0; i < fresh->entries.size(); ++i) {
        const HttpHeaderEntry *e = fresh->entries[i];
        if (!e || skipUpdateHeader(e->id))
            continue;
        String value;
        const char *name = e->name.termedBuf();
        if (!getByNameIfPresent(name, value) ||
                (value != fresh->getByName(name)))
            return true;
    }
    return false;
}