    {
        zl = createList();
        p = ziplistIndex(zl, 3);
        if (ziplistNext(p, &s) == NULL) {
            printf("No entry\n");
        } else {
            printf("ERROR\n");
