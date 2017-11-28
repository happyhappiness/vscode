void
DiskdFile::notifyClient()
{
    if (!canNotifyClient()) {
        return;
    }

    ioRequestor->ioCompletedNotification();
}