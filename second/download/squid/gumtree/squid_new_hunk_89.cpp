    storeAppendPrintf(entry, "%s %d seconds\n", name, (int) var);
}

void
parse_time_t(time_t * var)
{
    time_msec_t tval;
    parseTimeLine(&tval, T_SECOND_STR, false);
    *var = static_cast<time_t>(tval/1000);
}

static void
free_time_t(time_t * var)
{
    *var = 0;
}

#if !USE_DNSHELPER
static void
dump_time_msec(StoreEntry * entry, const char *name, time_msec_t var)
{
    if (var % 1000)
        storeAppendPrintf(entry, "%s %" PRId64 " milliseconds\n", name, var);
    else
        storeAppendPrintf(entry, "%s %d seconds\n", name, (int)(var/1000) );
}

void
parse_time_msec(time_msec_t * var)
{
    parseTimeLine(var, T_SECOND_STR, true);
}

static void
free_time_msec(time_msec_t * var)
{
    *var = 0;
}
#endif

#if UNUSED_CODE
static void
dump_size_t(StoreEntry * entry, const char *name, size_t var)
{
    storeAppendPrintf(entry, "%s %d\n", name, (int) var);
}
#endif

static void
dump_b_size_t(StoreEntry * entry, const char *name, size_t var)
{
    storeAppendPrintf(entry, "%s %d %s\n", name, (int) var, B_BYTES_STR);
}

#if !USE_DNSHELPER
static void
dump_b_ssize_t(StoreEntry * entry, const char *name, ssize_t var)
{
    storeAppendPrintf(entry, "%s %d %s\n", name, (int) var, B_BYTES_STR);
}
#endif

#if UNUSED_CODE
static void
dump_kb_size_t(StoreEntry * entry, const char *name, size_t var)
{
    storeAppendPrintf(entry, "%s %d %s\n", name, (int) var, B_KBYTES_STR);
}
