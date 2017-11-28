bool
IpcIoFile::canWrite() const
{
    return diskId >= 0 && canWait();
}