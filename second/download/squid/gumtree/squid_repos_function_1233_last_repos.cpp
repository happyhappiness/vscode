void
FileMap::grow()
{
    int old_sz = nwords * sizeof(*bitmap);
    void *old_map = bitmap;
    capacity_ <<= 1;
    assert(capacity_ <= (1 << 24)); /* swap_filen is 25 bits, signed */
    nwords = capacity_ >> LONG_BIT_SHIFT;
    debugs(8, 3, HERE << " creating space for " << capacity_ << " files");
    debugs(8, 5, "--> " << nwords << " words of " << sizeof(*bitmap) << " bytes each");
    bitmap = (unsigned long *)xcalloc(nwords, sizeof(*bitmap));
    debugs(8, 3, "copying " << old_sz << " old bytes");
    memcpy(bitmap, old_map, old_sz);
    xfree(old_map);
    /* XXX account fm->bitmap */
}