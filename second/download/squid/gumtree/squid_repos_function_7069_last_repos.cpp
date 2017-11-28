const Ipc::QueueReader &
Ipc::FewToFewBiQueue::localReader() const
{
    return readers->theReaders[readerIndex(theLocalGroup, theLocalProcessId)];
}