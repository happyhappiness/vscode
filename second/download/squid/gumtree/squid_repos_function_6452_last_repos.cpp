bool
IpcIoFile::canWrite() const
{
    return diskId >= 0 && !error_ && canWait();
}