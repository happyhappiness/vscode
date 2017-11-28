void
MmappedFile::close()
{
    debugs(79, 3, HERE << this << " closing for " << ioRequestor);
    doClose();
    assert(ioRequestor != NULL);
    ioRequestor->closeCompleted();
}