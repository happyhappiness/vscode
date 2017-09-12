    {
        zl = createList();
        p = ziplistIndex(zl, 0);
        while ((p = ziplistNext(p, &entry, &elen)) != NULL) {
            printf("Entry: ");
            fwrite(entry,elen,1,stdout);
            printf(" (length %d)\n", elen);
        }
        printf("\n");
    }
