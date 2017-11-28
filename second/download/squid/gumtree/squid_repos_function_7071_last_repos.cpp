int
Ipc::FewToFewBiQueue::remotesCount() const
{
    return theLocalGroup == groupA ? metadata->theGroupBSize :
           metadata->theGroupASize;
}