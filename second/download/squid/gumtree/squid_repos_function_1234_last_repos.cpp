bool
FileMap::setBit(sfileno file_number)
{
    unsigned long bitmask = (1L << (file_number & LONG_BIT_MASK));

    while (file_number >= capacity_)
        grow();

    bitmap[file_number >> LONG_BIT_SHIFT] |= bitmask;

    ++usedSlots_;

    return file_number;
}