    }
    *p = '\0';
    payload = strtoull(buf+1,NULL,10);
    if (!config.raw_output)
        printf("SYNC with master, discarding %lld bytes of bulk tranfer...\n",
            payload);

    /* Discard the payload. */
