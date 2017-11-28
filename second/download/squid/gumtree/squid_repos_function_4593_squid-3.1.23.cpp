void
CossSwapDir::ioCompletedNotification()
{
    if (theFile->error()) {
        debugs(47, 1, "" << path << ": " << xstrerror());
        fatal("storeCossDirInit: Failed to open a COSS file.");
    }
}