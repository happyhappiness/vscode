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
