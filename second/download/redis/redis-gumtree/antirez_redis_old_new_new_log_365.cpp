printf("AT RDB OFFSET: %llu\n",
        (unsigned long long) (rdbstate.rio ?
            rdbstate.rio->processed_bytes : 0));