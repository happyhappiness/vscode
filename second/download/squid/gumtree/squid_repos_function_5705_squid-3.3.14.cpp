void *
BlockingFile::operator new(size_t sz)
{
    CBDATA_INIT_TYPE(BlockingFile);
    BlockingFile *result = cbdataAlloc(BlockingFile);
    /* Mark result as being owned - we want the refcounter to do the delete
     * call */
    return result;
}