    {
        zl = createList();
        p = ziplistIndex(zl, 1);
        while ((p = ziplistNext(p, &s)) != NULL) {
            printf("Entry: %s (length %ld)\n", s, sdslen(s));
        }
        printf("\n");
    }
