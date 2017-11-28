int64_t
HttpHdrRange::lowestOffset(int64_t size) const
{
    int64_t offset = HttpHdrRangeSpec::UnknownPosition;
    const_iterator pos = begin();

    while (pos != end()) {
        int64_t current = (*pos)->offset;

        if (!known_spec(current)) {
            if ((*pos)->length > size || !known_spec((*pos)->length))
                return 0;   /* Unknown. Assume start of file */

            current = size - (*pos)->length;
        }

        if (current < offset || !known_spec(offset))
            offset = current;

        ++pos;
    }

    return known_spec(offset) ? offset : 0;
}