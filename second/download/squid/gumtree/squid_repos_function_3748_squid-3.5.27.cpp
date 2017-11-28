bool
HttpHdrRange::willBeComplex() const
{
    /* check that all rangers are in "strong" order, */
    /* as far as we can tell without the content length */
    int64_t offset = 0;

    for (const_iterator pos (begin()); pos != end(); ++pos) {
        if (!known_spec((*pos)->offset))    /* ignore unknowns */
            continue;

        /* Ensure typecasts is safe */
        assert ((*pos)->offset >= 0);

        if ((*pos)->offset < offset)
            return true;

        offset = (*pos)->offset;

        if (known_spec((*pos)->length)) /* avoid  unknowns */
            offset += (*pos)->length;
    }

    return false;
}