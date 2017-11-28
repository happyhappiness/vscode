fileMap *
file_map_create(void)
{
    fileMap *fm = (fileMap *)xcalloc(1, sizeof(fileMap));
    fm->max_n_files = FM_INITIAL_NUMBER;
    fm->nwords = fm->max_n_files >> LONG_BIT_SHIFT;
    debugs(8, 3, "file_map_create: creating space for " << fm->max_n_files << " files");
    debugs(8, 5, "--> " << fm->nwords << " words of " << sizeof(*fm->file_map) << " bytes each");
    fm->file_map = (unsigned long *)xcalloc(fm->nwords, sizeof(*fm->file_map));
    /* XXX account fm->file_map */
    return fm;
}