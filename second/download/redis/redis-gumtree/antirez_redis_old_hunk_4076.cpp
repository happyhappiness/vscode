    {
        zl = createList();
        p = ziplistIndex(zl, 2);
        while ((p = ziplistNext(p, &s)) != NULL) {
            printf("Entry: %s (length %ld)\n", s, sdslen(s));
        }
        printf("\n");
    }
