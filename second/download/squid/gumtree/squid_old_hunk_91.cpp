static void
free_size_t(size_t * var)
{
    *var = 0;
}

static void
free_b_int64_t(int64_t * var)
{
    *var = 0;
}

#define free_b_size_t free_size_t
#define free_kb_size_t free_size_t
#define free_mb_size_t free_size_t
#define free_gb_size_t free_size_t
#define free_kb_int64_t free_b_int64_t

static void
dump_ushort(StoreEntry * entry, const char *name, unsigned short var)
{
    storeAppendPrintf(entry, "%s %d\n", name, var);
}

static void
free_ushort(unsigned short * u)
{
    *u = 0;
}

static void
parse_ushort(unsigned short * var)
{
    ConfigParser::ParseUShort(var);
}

void
ConfigParser::ParseUShort(unsigned short *var)
