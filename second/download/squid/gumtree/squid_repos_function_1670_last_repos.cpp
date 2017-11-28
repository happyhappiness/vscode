static void
httpHdrRangeRespSpecPackInto(const HttpHdrRangeSpec * spec, Packable * p)
{
    /* Ensure typecast is safe */
    assert (spec->length >= 0);

    if (!known_spec(spec->offset) || !known_spec(spec->length))
        p->append("*", 1);
    else
        p->appendf("bytes %" PRId64 "-%" PRId64, spec->offset, spec->offset + spec->length - 1);
}