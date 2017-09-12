    }

    long pos = process(fp);
    if (pos < size) {
        if (fix) {
            if (ftruncate(fileno(fp), pos) == -1) {
                printf("Could not truncate AOF to size %ld\n", pos);
                exit(1);
            } else {
                printf("AOF succesfully truncated to %ld bytes\n", pos);
            }
        } else {
            printf("First invalid operation at offset %ld\n", pos);
        }
    } else {
        printf("AOF is valid\n");
