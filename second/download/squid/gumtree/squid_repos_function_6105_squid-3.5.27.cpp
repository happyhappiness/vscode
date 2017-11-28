bool
DiskThreadsDiskFile::ioInProgress() const
{
    return inProgressIOs > 0;
}