        args = args->next;
    }

    storeAppendPrintf(entry, "\n");
}

#include "cf_parser.cci"

peer_t
parseNeighborType(const char *s)
{
    if (!strcasecmp(s, "parent"))
