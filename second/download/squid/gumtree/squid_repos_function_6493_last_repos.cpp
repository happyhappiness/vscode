void
BlockingFile::close()
{
    debugs(79, 3, "BlockingFile::close: " << this << " closing for " << ioRequestor.getRaw());
    doClose();
    assert (ioRequestor.getRaw());
    ioRequestor->closeCompleted();
}