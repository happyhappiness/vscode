void
HttpHdrRange::packInto(Packer * packer) const
{
    const_iterator pos = begin();

    while (pos != end()) {
        if (pos != begin())
            packerAppend(packer, ",", 1);

        (*pos)->packInto(packer);

        ++pos;
    }
}