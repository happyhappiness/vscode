size_t
cacheDigestCalcMaskSize(int cap, int bpe)
{
    return (size_t) (cap * bpe + 7) / 8;
}