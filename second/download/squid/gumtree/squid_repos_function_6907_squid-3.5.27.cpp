int
Ipc::FewToFewBiQueue::remotesIdOffset() const
{
    return theLocalGroup == groupA ? metadata->theGroupBIdOffset :
           metadata->theGroupAIdOffset;
}