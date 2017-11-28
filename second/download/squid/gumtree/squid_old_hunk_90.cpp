static void
dump_kb_int64_t(StoreEntry * entry, const char *name, int64_t var)
{
    storeAppendPrintf(entry, "%s %" PRId64 " %s\n", name, var, B_KBYTES_STR);
}

static void
parse_size_t(size_t * var)
{
    int i;
    i = GetInteger();
    *var = (size_t) i;
}

static void
parse_b_size_t(size_t * var)
{
    parseBytesLine(var, B_BYTES_STR);
}

#if UNUSED_CODE
static void
parse_kb_size_t(size_t * var)
{
    parseBytesLine(var, B_KBYTES_STR);
}
