bool
HttpHdrRange::isComplex() const
{
    int64_t offset = 0;
    /* check that all rangers are in "strong" order */
    const_iterator pos (begin());

    while (pos != end()) {
        /* Ensure typecasts is safe */
        assert ((*pos)->offset >= 0);

        if ((*pos)->offset < offset)
            return 1;

        offset = (*pos)->offset + (*pos)->length;

        ++pos;
    }

    return 0;
}