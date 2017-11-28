        args = args->next;
    }

    storeAppendPrintf(entry, "\n");
}

void
YesNoNone::configure(bool beSet)
{
    option = beSet ? +1 : -1;
}

YesNoNone::operator void*() const
{
    assert(option != 0); // must call configure() first
    return option > 0 ? (void*)this : NULL;
}


inline void
free_YesNoNone(YesNoNone *)
{
    // do nothing: no explicit cleanup is required
}

static void
parse_YesNoNone(YesNoNone *option)
{
    int value = 0;
    parse_onoff(&value);
    option->configure(value > 0);
}

static void
dump_YesNoNone(StoreEntry * entry, const char *name, YesNoNone &option)
{
    if (option.configured())
        dump_onoff(entry, name, option ? 1 : 0);
}

static void
free_memcachemode(SquidConfig * config)
{
    return;
}

static void
parse_memcachemode(SquidConfig * config)
{
    char *token = strtok(NULL, w_space);
    if (!token)
        self_destruct();

    if (strcmp(token, "always") == 0) {
        Config.onoff.memory_cache_first = 1;
        Config.onoff.memory_cache_disk = 1;
    } else if (strcmp(token, "disk") == 0) {
        Config.onoff.memory_cache_first = 0;
        Config.onoff.memory_cache_disk = 1;
    } else if (strncmp(token, "net", 3) == 0) {
        Config.onoff.memory_cache_first = 1;
        Config.onoff.memory_cache_disk = 0;
    } else if (strcmp(token, "never") == 0) {
        Config.onoff.memory_cache_first = 0;
        Config.onoff.memory_cache_disk = 0;
    } else
        self_destruct();
}

static void
dump_memcachemode(StoreEntry * entry, const char *name, SquidConfig &config)
{
    storeAppendPrintf(entry, "%s ", name);
    if (Config.onoff.memory_cache_first && Config.onoff.memory_cache_disk)
        storeAppendPrintf(entry, "always");
    else if (!Config.onoff.memory_cache_first && Config.onoff.memory_cache_disk)
        storeAppendPrintf(entry, "disk");
    else if (Config.onoff.memory_cache_first && !Config.onoff.memory_cache_disk)
        storeAppendPrintf(entry, "network");
    else if (!Config.onoff.memory_cache_first && !Config.onoff.memory_cache_disk)
        storeAppendPrintf(entry, "none");
    storeAppendPrintf(entry, "\n");
}

#include "cf_parser.cci"

peer_t
parseNeighborType(const char *s)
{
    if (!strcasecmp(s, "parent"))
