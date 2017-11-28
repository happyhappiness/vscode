HttpHdrRange *
HttpHdrRange::ParseCreate(const String * range_spec)
{
    HttpHdrRange *r = new HttpHdrRange;

    if (!r->parseInit(range_spec)) {
        delete r;
        r = NULL;
    }

    return r;
}