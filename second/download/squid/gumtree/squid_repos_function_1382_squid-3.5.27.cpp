void
StringRegistry::Stat(StoreEntry *entry)
{
    storeAppendPrintf(entry, "%lu entries, %lu reported from MemPool\n", (unsigned long) Instance().entries.elements, (unsigned long) memStringCount());
    Instance().entries.head->walk(Stater, entry);
}