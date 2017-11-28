bool
FileMap::testBit(sfileno file_number) const
{
    unsigned long bitmask = (1L << (file_number & LONG_BIT_MASK));

    if (file_number >= capacity_)
        return 0;

    /* be sure the return value is an int, not a u_long */
    return (bitmap[file_number >> LONG_BIT_SHIFT] & bitmask ? 1 : 0);
}