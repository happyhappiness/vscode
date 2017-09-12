    {
        zl = createList();
        p = ziplistIndex(zl, 2);
        while ((p = ziplistNext(p, NULL, &entry, &elen)) != NULL) {
            printf("Entry: ");
            fwrite(entry,elen,1,stdout);
            printf(" (length %d)\n", elen);
        }
        printf("\n");
    }

    printf("Iterate starting out of range:\n");
    {
        zl = createList();
        p = ziplistIndex(zl, 3);
        if (ziplistNext(p, &entry, NULL, &elen) == NULL) {
            printf("No entry\n");
        } else {
            printf("ERROR\n");
