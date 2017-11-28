bool
StoreSearchHashIndex::next()
{
    if (entries.size())
        entries.pop_back();

    while (!isDone() && !entries.size())
        copyBucket();

    return currentItem() != NULL;
}