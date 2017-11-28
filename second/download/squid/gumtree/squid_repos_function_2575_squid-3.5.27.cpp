static void
cacheDigestInit(CacheDigest * cd, uint64_t capacity, uint8_t bpe)
{
    const uint32_t mask_size = cacheDigestCalcMaskSize(capacity, bpe);
    assert(cd);
    assert(capacity > 0 && bpe > 0);
    assert(mask_size != 0);
    cd->capacity = capacity;
    cd->bits_per_entry = bpe;
    cd->mask_size = mask_size;
    cd->mask = (char *)xcalloc(cd->mask_size, 1);
    debugs(70, 2, "cacheDigestInit: capacity: " << cd->capacity << " entries, bpe: " << cd->bits_per_entry << "; size: "
           << cd->mask_size << " bytes");
}