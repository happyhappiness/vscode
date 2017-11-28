const Ipc::QueueReader::Balance &
Ipc::FewToFewBiQueue::balance(const int remoteProcessId) const
{
    const QueueReader &r = reader(remoteGroup(), remoteProcessId);
    return r.balance;
}