off_t
CossSwapDir::storeCossFilenoToDiskOffset(sfileno f)
{
    return (off_t) f << blksz_bits;
}