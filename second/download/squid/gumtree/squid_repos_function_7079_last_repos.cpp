const Ipc::QueueReader &
Ipc::MultiQueue::localReader() const
{
    return reader(theLocalProcessId);
}