            );
    }

    /* Allocation statistics */
    if (allsections || !strcasecmp(section,"allocstats")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscat(info, "# Allocstats\r\nallocation_stats:");
        for (j = 0; j <= ZMALLOC_MAX_ALLOC_STAT; j++) {
            size_t count = zmalloc_allocations_for_size(j);
            if (count) {
                if (info[sdslen(info)-1] != ':') info = sdscatlen(info,",",1);
                info = sdscatprintf(info,"%s%d=%zu",
                    (j == ZMALLOC_MAX_ALLOC_STAT) ? ">=" : "",
                    j,count);
            }
        }
        info = sdscat(info,"\r\n");
    }

    /* Persistence */
    if (allsections || defsections || !strcasecmp(section,"persistence")) {
        if (sections++) info = sdscat(info,"\r\n");
