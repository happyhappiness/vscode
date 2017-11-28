bool
DiskdFile::ioInProgress()const
{
    return inProgressIOs != 0;
}