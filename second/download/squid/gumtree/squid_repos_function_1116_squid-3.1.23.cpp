static void
dump_ushort(StoreEntry * entry, const char *name, unsigned short var)
{
    storeAppendPrintf(entry, "%s %d\n", name, var);
}