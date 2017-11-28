void
MmappedFile::create(int flags, mode_t mode, RefCount<IORequestor> callback)
{
    /* We use the same logic path for open */
    open(flags, mode, callback);
}