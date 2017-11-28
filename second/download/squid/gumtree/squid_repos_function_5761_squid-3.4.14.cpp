bool
IpcIoFile::canRead() const
{
    return diskId >= 0 && canWait();
}