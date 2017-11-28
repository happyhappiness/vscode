int
Ipc::FewToFewBiQueue::readerIndex(const Group group, const int processId) const
{
    Must(validProcessId(group, processId));
    return group == groupA ?
           processId - metadata->theGroupAIdOffset :
           metadata->theGroupASize + processId - metadata->theGroupBIdOffset;
}