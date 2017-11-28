static int
httpHdrRangeRespSpecParseInit(HttpHdrRangeSpec * spec, const char *field, int flen)
{
    const char *p;
    assert(spec);
    spec->offset = spec->length = range_spec_unknown;

    if (flen < 2)
        return 0;

    /* is spec given ? */
    if (*field == '*')
        return 1;

    /* check format, must be %d-%d */
    if (!((p = strchr(field, '-')) && (p - field < flen))) {
        debugs(68, 2, "invalid (no '-') resp-range-spec near: '" << field << "'");
        return 0;
    }

    /* parse offset */
    if (!httpHeaderParseOffset(field, &spec->offset))
        return 0;

    /* Additional check for BUG2155 - there MUST BE first-byte-pos and it MUST be positive*/
    if (spec->offset < 0) {
        debugs(68, 2, "invalid (no first-byte-pos or it is negative) resp-range-spec near: '" << field << "'");
        return 0;
    }

    ++p;

    /* do we have last-pos ? */
    if (p - field >= flen) {
        debugs(68, 2, "invalid (no last-byte-pos) resp-range-spec near: '" << field << "'");
        return 0;
    }

    int64_t last_pos;

    if (!httpHeaderParseOffset(p, &last_pos))
        return 0;

    if (last_pos < spec->offset) {
        debugs(68, 2, "invalid (negative last-byte-pos) resp-range-spec near: '" << field << "'");
        return 0;
    }

    spec->length = size_diff(last_pos + 1, spec->offset);

    /* we managed to parse, check if the result makes sence */
    if (spec->length <= 0) {
        debugs(68, 2, "invalid range (" << spec->offset << " += " <<
               (long int) spec->length << ") in resp-range-spec near: '" << field << "'");
        return 0;
    }

    return 1;
}