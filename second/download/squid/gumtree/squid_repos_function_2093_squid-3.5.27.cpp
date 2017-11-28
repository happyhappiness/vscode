bool
StoreSearchHashIndex::next()
{
    if (!entries.empty())
        entries.pop_back();

    while (!isDone() && !entries.size())
        copyBucket();

    return currentItem() != NULL;
}