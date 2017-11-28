int64_t
HttpHdrRange::firstOffset() const
{
    int64_t offset = HttpHdrRangeSpec::UnknownPosition;
    const_iterator pos = begin();

    while (pos != end()) {
        if ((*pos)->offset < offset || !known_spec(offset))
            offset = (*pos)->offset;

        ++pos;
    }

    return offset;
}