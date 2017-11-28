void
IpcIoFile::create(int flags, mode_t mode, RefCount<IORequestor> callback)
{
    assert(false); // check
    /* We use the same logic path for open */
    open(flags, mode, callback);
}