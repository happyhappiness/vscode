void
HttpHdrRange::packInto(Packable * packer) const
{
    const_iterator pos = begin();

    while (pos != end()) {
        if (pos != begin())
            packer->append(",", 1);

        (*pos)->packInto(packer);

        ++pos;
    }
}