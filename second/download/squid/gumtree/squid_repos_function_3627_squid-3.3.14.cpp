HttpHdrRangeSpec *
HttpHdrRangeSpec::Create(const char *field, int flen)
{
    HttpHdrRangeSpec spec;

    if (!spec.parseInit(field, flen))
        return NULL;

    return new HttpHdrRangeSpec(spec);
}