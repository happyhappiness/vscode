const StoreEntry *
UFSCleanLog::nextEntry()
{
    const StoreEntry *entry = NULL;

    if (walker)
        entry = walker->Next(walker);

    return entry;
}