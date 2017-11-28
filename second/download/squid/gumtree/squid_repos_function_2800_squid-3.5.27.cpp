int
HttpHeader::delByName(const char *name)
{
    int count = 0;
    HttpHeaderPos pos = HttpHeaderInitPos;
    HttpHeaderEntry *e;
    httpHeaderMaskInit(&mask, 0);   /* temporal inconsistency */
    debugs(55, 9, "deleting '" << name << "' fields in hdr " << this);

    while ((e = getEntry(&pos))) {
        if (!e->name.caseCmp(name))
            delAt(pos, count);
        else
            CBIT_SET(mask, e->id);
    }

    return count;
}