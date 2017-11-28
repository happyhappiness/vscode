bool
HttpHdrRangeSpec::parseInit(const char *field, int flen)
{
    const char *p;

    if (flen < 2)
        return false;

    /* is it a suffix-byte-range-spec ? */
    if (*field == '-') {
        if (!httpHeaderParseOffset(field + 1, &length))
            return false;
    } else
        /* must have a '-' somewhere in _this_ field */
        if (!((p = strchr(field, '-')) || (p - field >= flen))) {
            debugs(64, 2, "invalid (missing '-') range-spec near: '" << field << "'");
            return false;
        } else {
            if (!httpHeaderParseOffset(field, &offset))
                return false;

            p++;

            /* do we have last-pos ? */
            if (p - field < flen) {
                int64_t last_pos;

                if (!httpHeaderParseOffset(p, &last_pos))
                    return false;

                // RFC 2616 s14.35.1 MUST: last-byte-pos >= first-byte-pos
                if (last_pos < offset) {
                    debugs(64, 2, "invalid (last-byte-pos < first-byte-pos) range-spec near: " << field);
                    return false;
                }

                HttpHdrRangeSpec::HttpRange aSpec (offset, last_pos + 1);

                length = aSpec.size();
            }
        }

    return true;
}