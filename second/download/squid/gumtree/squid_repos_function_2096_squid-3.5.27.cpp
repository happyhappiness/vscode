StoreEntry *
StoreSearchHashIndex::currentItem()
{
    if (!entries.size())
        return NULL;

    return entries.back();
}