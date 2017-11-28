void
DiskThreadsDiskFile::close()
{
    debugs(79, 3, "DiskThreadsDiskFile::close: " << this << " closing for " << ioRequestor.getRaw());

    if (!ioInProgress()) {
        doClose();
        assert (ioRequestor != NULL);
        ioRequestor->closeCompleted();
        return;
    } else {
        debugs(79,0,HERE << "DiskThreadsDiskFile::close: " <<
               "did NOT close because ioInProgress() is true.  now what?");
    }
}