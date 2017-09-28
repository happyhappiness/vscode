    printf("# per 100 SCAN commands (not usually needed).\n\n");

    /* New up sds strings to keep track of overall biggest per type */
    for(i=0;i<TYPE_NONE; i++) {
        maxkeys[i] = sdsempty();
        if(!maxkeys[i]) {
            fprintf(stderr, "Failed to allocate memory for largest key names!\n");
            exit(1);
        }
    }

    /* SCAN loop */
    do {
