    printf("Pop head: %s (length %ld)\n", s, sdslen(s));
    ziplistRepr(zl);

    return 0;
}
#endif
