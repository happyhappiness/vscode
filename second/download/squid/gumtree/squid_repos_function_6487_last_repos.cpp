DiskFile::Pointer
IpcIoIOStrategy::newFile (char const *path)
{
    return new IpcIoFile (path);
}