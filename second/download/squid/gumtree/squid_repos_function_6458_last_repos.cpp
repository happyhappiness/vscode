bool
IpcIoFile::ioInProgress() const
{
    return !olderRequests->empty() || !newerRequests->empty();
}