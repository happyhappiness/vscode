                (long long) sdsavail(val->ptr),
                (long long) getStringObjectSdsUsedMemory(val));
        }
    } else if (!strcasecmp(c->argv[1]->ptr,"populate") &&
               (c->argc == 3 || c->argc == 4)) {
        long keys, j;
