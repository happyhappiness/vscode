    }
    *p = '\0';
    payload = strtoull(buf+1,NULL,10);
    fprintf(stderr,"SYNC with master, discarding %lld bytes of bulk tranfer...\n",
            payload);

    /* Discard the payload. */
