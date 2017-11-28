bool
Fs::Ufs::StoreSearchUFS::next()
{
    /* the walker API doesn't make sense. the store entries referred to are already readwrite
     * from their hash table entries
     */

    if (walker)
        current = const_cast<StoreEntry *>(walker->Next(walker));

    if (current == NULL)
        _done = true;

    return current != NULL;
}