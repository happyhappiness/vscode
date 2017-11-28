void *
MmappedFile::operator new(size_t sz)
{
    CBDATA_INIT_TYPE(MmappedFile);
    MmappedFile *result = cbdataAlloc(MmappedFile);
    /* Mark result as being owned - we want the refcounter to do the delete
     * call */
    return result;
}