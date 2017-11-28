bool
Ipc::MultiQueue::validProcessId(const int processId) const
{
    return metadata->theProcessIdOffset <= processId &&
           processId < metadata->theProcessIdOffset + metadata->theProcessCount;
}