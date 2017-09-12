    {
        zl = createList();
        p = ziplistIndex(zl, 3);
        if (ziplistNext(p, &entry, &elen) == NULL) {
            printf("No entry\n");
        } else {
            printf("ERROR\n");
