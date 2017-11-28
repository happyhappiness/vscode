StoreEntry *
Store::LocalSearch::currentItem()
{
    if (!entries.size())
        return NULL;

    return entries.back();
}