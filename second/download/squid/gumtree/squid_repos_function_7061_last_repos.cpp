Ipc::FewToFewBiQueue::Owner *
Ipc::FewToFewBiQueue::Init(const String &id, const int groupASize, const int groupAIdOffset, const int groupBSize, const int groupBIdOffset, const unsigned int maxItemSize, const int capacity)
{
    return new Owner(id, groupASize, groupAIdOffset, groupBSize, groupBIdOffset, maxItemSize, capacity);
}