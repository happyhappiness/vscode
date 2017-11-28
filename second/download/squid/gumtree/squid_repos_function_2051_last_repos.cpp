void
CacheDigest::init(uint64_t newCapacity)
{
    const auto newMaskSz = CacheDigest::CalcMaskSize(newCapacity, bits_per_entry);
    assert(newCapacity > 0 && bits_per_entry > 0);
    assert(newMaskSz != 0);
    capacity = newCapacity;
    mask_size = newMaskSz;
    mask = static_cast<char *>(xcalloc(mask_size,1));
    debugs(70, 2, "capacity: " << capacity << " entries, bpe: " << bits_per_entry << "; size: "
           << mask_size << " bytes");
}