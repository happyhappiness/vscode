}

void
CossSwapDir::ioCompletedNotification()
{
    if (theFile->error()) {
        debugs(47, DBG_IMPORTANT, "" << path << ": " << xstrerror());
        fatal("storeCossDirInit: Failed to open a COSS file.");
    }
}

void
CossSwapDir::closeCompleted()
