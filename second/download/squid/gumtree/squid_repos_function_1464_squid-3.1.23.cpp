static void
file_map_grow(fileMap * fm)
{
    int old_sz = fm->nwords * sizeof(*fm->file_map);
    void *old_map = fm->file_map;
    fm->max_n_files <<= 1;
    assert(fm->max_n_files <= (1 << 24));	/* swap_filen is 25 bits, signed */
    fm->nwords = fm->max_n_files >> LONG_BIT_SHIFT;
    debugs(8, 3, "file_map_grow: creating space for " << fm->max_n_files << " files");
    fm->file_map = (unsigned long *)xcalloc(fm->nwords, sizeof(*fm->file_map));
    debugs(8, 3, "copying " << old_sz << " old bytes");
    xmemcpy(fm->file_map, old_map, old_sz);
    xfree(old_map);
    /* XXX account fm->file_map */
}