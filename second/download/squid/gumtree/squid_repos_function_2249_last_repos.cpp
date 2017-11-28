bool
HttpHeader::needUpdate(HttpHeader const *fresh) const
{
    for (const auto e: fresh->entries) {
        if (!e || skipUpdateHeader(e->id))
            continue;
        String value;
        const char *name = e->name.termedBuf();
        if (!hasNamed(name, strlen(name), &value) ||
                (value != fresh->getByName(name)))
            return true;
    }
    return false;
}