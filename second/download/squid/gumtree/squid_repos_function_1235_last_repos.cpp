void
FileMap::clearBit(sfileno file_number)
{
    unsigned long bitmask = (1L << (file_number & LONG_BIT_MASK));
    bitmap[file_number >> LONG_BIT_SHIFT] &= ~bitmask;
    --usedSlots_;
}