Ipc::QueueReader::Balance &
Ipc::FewToFewBiQueue::localBalance()
{
    QueueReader &r = reader(theLocalGroup, theLocalProcessId);
    return r.balance;
}