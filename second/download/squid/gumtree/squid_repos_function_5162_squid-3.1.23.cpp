void *
DiskdFile::operator new(size_t unused)
{
    CBDATA_INIT_TYPE(DiskdFile);
    DiskdFile *result = cbdataAlloc(DiskdFile);
    /* Mark result as being owned - we want the refcounter to do the delete
     * call */
    debugs(79, 3, "diskdFile with base " << result << " allocating");
    return result;
}