int
Ipc::FewToFewBiQueue::MaxItemsCount(const int groupASize, const int groupBSize, const int capacity)
{
    return capacity * groupASize * groupBSize * 2;
}