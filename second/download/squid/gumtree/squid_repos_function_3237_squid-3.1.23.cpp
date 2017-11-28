static void
storeEntryAppend(StoreEntry *e, const char *buf, int len)
{
    e->append(buf, len);
}