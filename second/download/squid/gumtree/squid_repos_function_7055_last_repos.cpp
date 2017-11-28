const Ipc::QueueReader::Balance &
Ipc::BaseMultiQueue::balance(const int remoteProcessId) const
{
    const QueueReader &r = remoteReader(remoteProcessId);
    return r.balance;
}