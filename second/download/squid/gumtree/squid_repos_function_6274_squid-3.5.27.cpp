bool
IpcIoFile::canRead() const
{
    return diskId >= 0 && !error_ && canWait();
}