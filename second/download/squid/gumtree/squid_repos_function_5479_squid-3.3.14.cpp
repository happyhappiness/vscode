void *
DiskThreadsDiskFile::operator new (size_t)
{
    CBDATA_INIT_TYPE(DiskThreadsDiskFile);
    DiskThreadsDiskFile *result = cbdataAlloc(DiskThreadsDiskFile);
    /*
     * We used to call squidaio_init() here, but if the first transaction
     * is to unlink a file (e.g., if Squid starts up over the disk space
     * limit) then "squidaio" won't be initialized yet.
     */

    return result;
}