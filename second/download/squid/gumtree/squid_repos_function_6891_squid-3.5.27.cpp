const Ipc::QueueReader::Rate &
Ipc::BaseMultiQueue::rateLimit(const int remoteProcessId) const
{
    const QueueReader &r = remoteReader(remoteProcessId);
    return r.rateLimit;
}