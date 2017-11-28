const StoreEntry *
CossCleanLog::nextEntry()
{
    const StoreEntry *entry;

    if (!current)
        return NULL;

    entry = (const StoreEntry *) current->data;

    current = current->prev;

    return entry;
}