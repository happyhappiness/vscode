static void
dump_b_int64_t(StoreEntry * entry, const char *name, int64_t var)
{
    storeAppendPrintf(entry, "%s %" PRId64 " %s\n", name, var, B_BYTES_STR);
}