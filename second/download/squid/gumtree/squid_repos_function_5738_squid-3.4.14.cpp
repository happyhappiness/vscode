bool
DiskdFile::canNotifyClient() const
{
    if (!ioRequestor.getRaw()) {
        debugs(79, 3, "DiskdFile::canNotifyClient: No ioRequestor to notify");
        return false;
    }

    return true;
}