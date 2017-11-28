void
HttpHdrRangeSpec::packInto(Packable * p) const
{
    if (!known_spec(offset))    /* suffix */
        p->appendf("-%" PRId64, length);
    else if (!known_spec(length))       /* trailer */
        p->appendf("%" PRId64 "-", offset);
    else            /* range */
        p->appendf("%" PRId64 "-%" PRId64, offset, offset + length - 1);
}