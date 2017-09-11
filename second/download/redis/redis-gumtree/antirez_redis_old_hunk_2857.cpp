        exit(1);
    }

    long size = sb.st_size;
    if (size == 0) {
        printf("Empty file: %s\n", filename);
        exit(1);
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
