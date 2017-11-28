bool
HttpHdrRange::parseInit(const String * range_spec)
{
    const char *item;
    const char *pos = NULL;
    int ilen;
    assert(this && range_spec);
    ++ParsedCount;
    debugs(64, 8, "parsing range field: '" << range_spec << "'");
    /* check range type */

    if (range_spec->caseCmp("bytes=", 6))
        return 0;

    /* skip "bytes="; hack! */
    pos = range_spec->termedBuf() + 6;

    /* iterate through comma separated list */
    while (strListGetItem(range_spec, ',', &item, &ilen, &pos)) {
        HttpHdrRangeSpec *spec = HttpHdrRangeSpec::Create(item, ilen);
        /*
         * RFC 2616 section 14.35.1: MUST ignore Range with
         * at least one syntactically invalid byte-range-specs.
         */
        if (!spec) {
            while (!specs.empty())
                delete specs.pop_back();
            debugs(64, 2, "ignoring invalid range field: '" << range_spec << "'");
            break;
        }

        specs.push_back(spec);
    }

    debugs(64, 8, "got range specs: " << specs.size());
    return !specs.empty();
}