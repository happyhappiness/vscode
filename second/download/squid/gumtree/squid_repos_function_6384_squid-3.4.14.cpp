Ipc::QueueReader::Rate &
Ipc::FewToFewBiQueue::localRateLimit()
{
    QueueReader &r = reader(theLocalGroup, theLocalProcessId);
    return r.rateLimit;
}