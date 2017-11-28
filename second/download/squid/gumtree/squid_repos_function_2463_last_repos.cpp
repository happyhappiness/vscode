bool
StoreEntry::checkDeferRead(int) const
{
    return (bytesWanted(Range<size_t>(0,INT_MAX)) == 0);
}