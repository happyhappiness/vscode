const Ipc::QueueReader::Rate &
Ipc::FewToFewBiQueue::rateLimit(const int remoteProcessId) const
{
    const QueueReader &r = reader(remoteGroup(), remoteProcessId);
    return r.rateLimit;
}