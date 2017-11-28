void *
AIODiskFile::operator new(size_t unused)
{
    CBDATA_INIT_TYPE(AIODiskFile);
    return cbdataAlloc(AIODiskFile);
}