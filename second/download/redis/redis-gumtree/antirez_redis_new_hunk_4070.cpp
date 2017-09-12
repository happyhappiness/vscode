    {
        zl = createList();
        p = ziplistIndex(zl, 2);
        while ((p = ziplistNext(p, NULL, &entry, &elen)) != NULL) {
            printf("Entry: ");
            fwrite(entry,elen,1,stdout);
            printf(" (length %d)\n", elen);
