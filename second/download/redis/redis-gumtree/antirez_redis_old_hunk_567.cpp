            _prefix = sdscat(sdsnew(prefix),_prefixlen);

            /* Setup prefix format for every entry */
            snprintf(_prefixfmt,sizeof(_prefixfmt),"%%s%%%dd) ",idxlen);

            for (i = 0; i < r->elements; i++) {
                /* Don't use the prefix for the first element, as the parent
