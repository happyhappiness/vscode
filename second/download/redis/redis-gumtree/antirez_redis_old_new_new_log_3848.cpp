addReplySds(c,sdscatprintf(sdsempty(),
                "+Value swapped at: page %llu "
                "using %llu pages\r\n",
                (unsigned long long) vp->page,
                (unsigned long long) vp->usedpages));