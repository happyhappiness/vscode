int
Ipc::FewToFewBiQueue::oneToOneQueueIndex(const Group fromGroup, const int fromProcessId, const Group toGroup, const int toProcessId) const
{
    Must(fromGroup != toGroup);
    assert(validProcessId(fromGroup, fromProcessId));
    assert(validProcessId(toGroup, toProcessId));
    int index1;
    int index2;
    int offset;
    if (fromGroup == groupA) {
        index1 = fromProcessId - metadata->theGroupAIdOffset;
        index2 = toProcessId - metadata->theGroupBIdOffset;
        offset = 0;
    } else {
        index1 = toProcessId - metadata->theGroupAIdOffset;
        index2 = fromProcessId - metadata->theGroupBIdOffset;
        offset = metadata->theGroupASize * metadata->theGroupBSize;
    }
    const int index = offset + index1 * metadata->theGroupBSize + index2;
    return index;
}