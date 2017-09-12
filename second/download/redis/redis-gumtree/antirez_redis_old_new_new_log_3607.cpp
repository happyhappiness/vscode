printf(
        "{total bytes %d} "
        "{length %u}\n"
        "{tail offset %u}\n",
        ZIPLIST_BYTES(zl),
        ZIPLIST_LENGTH(zl),
        ZIPLIST_TAIL_OFFSET(zl));