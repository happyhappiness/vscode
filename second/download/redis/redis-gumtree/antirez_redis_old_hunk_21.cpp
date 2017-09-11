        exit(1);
    }

    off_t pos = process(fp);
    off_t diff = size-pos;
    printf("AOF analyzed: size=%lld, ok_up_to=%lld, diff=%lld\n",
