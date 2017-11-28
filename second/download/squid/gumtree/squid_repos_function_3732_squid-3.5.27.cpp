void
HttpHdrRangeSpec::packInto(Packer * packer) const
{
    if (!known_spec(offset))    /* suffix */
        packerPrintf(packer, "-%" PRId64,  length);
    else if (!known_spec(length))       /* trailer */
        packerPrintf(packer, "%" PRId64 "-", offset);
    else            /* range */
        packerPrintf(packer, "%" PRId64 "-%" PRId64,
                     offset, offset + length - 1);
}