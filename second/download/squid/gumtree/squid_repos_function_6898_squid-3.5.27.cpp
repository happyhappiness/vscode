bool
Ipc::FewToFewBiQueue::validProcessId(const Group group, const int processId) const
{
    switch (group) {
    case groupA:
        return metadata->theGroupAIdOffset <= processId &&
               processId < metadata->theGroupAIdOffset + metadata->theGroupASize;
    case groupB:
        return metadata->theGroupBIdOffset <= processId &&
               processId < metadata->theGroupBIdOffset + metadata->theGroupBSize;
    }
    return false;
}