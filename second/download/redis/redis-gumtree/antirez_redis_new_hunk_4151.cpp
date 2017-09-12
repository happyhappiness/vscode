    }

    long pos = process(fp);
    long diff = size-pos;
    if (diff > 0) {
        if (fix) {
            char buf[2];
            printf("This will shrink the AOF from %ld bytes, with %ld bytes, to %ld bytes\n",size,diff,pos);
            printf("Continue? [y/N]: ");
            if (fgets(buf,sizeof(buf),stdin) == NULL ||
                strncasecmp(buf,"y",1) != 0) {
                    printf("Aborting...\n");
                    exit(1);
            }
            if (ftruncate(fileno(fp), pos) == -1) {
                printf("Failed to truncate AOF\n");
                exit(1);
            } else {
                printf("Successfully truncated AOF\n");
            }
        } else {
            printf("AOF is not valid\n");
            exit(1);
        }
    } else {
        printf("AOF is valid\n");
