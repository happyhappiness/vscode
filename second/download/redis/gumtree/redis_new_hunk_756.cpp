    off_t size = sb.st_size;
    if (size == 0) {
        printf("Empty file: %s\n", filename);
        exit(1);
    }

    /* This AOF file may have an RDB preamble. Check this to start, and if this
     * is the case, start processing the RDB part. */
    if (size >= 8) {    /* There must be at least room for the RDB header. */
        char sig[5];
        int has_preamble = fread(sig,sizeof(sig),1,fp) == 1 &&
                            memcmp(sig,"REDIS",sizeof(sig)) == 0;
        rewind(fp);
        if (has_preamble) {
            printf("The AOF appears to start with an RDB preamble.\n"
                   "Checking the RDB preamble to start:\n");
            if (redis_check_rdb_main(argc,argv,fp) == C_ERR) {
                printf("RDB preamble of AOF file is not sane, aborting.\n");
                exit(1);
            } else {
                printf("RDB preamble is OK, proceding with AOF tail...\n");
            }
        }
    }

    off_t pos = process(fp);
    off_t diff = size-pos;
    printf("AOF analyzed: size=%lld, ok_up_to=%lld, diff=%lld\n",
        (long long) size, (long long) pos, (long long) diff);
    if (diff > 0) {
        if (fix) {
