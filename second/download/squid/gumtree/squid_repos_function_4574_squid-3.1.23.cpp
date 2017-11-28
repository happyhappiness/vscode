sfileno
CossSwapDir::storeCossDiskOffsetToFileno(off_t o)
{
    assert(0 == (o & blksz_mask));
    return o >> blksz_bits;
}