uint32_t
cacheDigestCalcMaskSize(uint64_t cap, uint8_t bpe)
{
    uint64_t bitCount = (cap * bpe) + 7;
    assert(bitCount < INT_MAX); // dont 31-bit overflow later
    return static_cast<uint32_t>(bitCount / 8);
}