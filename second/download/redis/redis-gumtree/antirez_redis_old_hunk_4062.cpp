    {
        zl = createList();
        p = ziplistIndex(zl, 0);
        while ((p = ziplistNext(p, &q, &entry, &elen)) != NULL) {
            if (strncmp("foo", entry, elen) == 0) {
                printf("Delete foo\n");
                zl = ziplistDelete(zl, &q);
                p = q;
            } else {
                printf("Entry: ");
                fwrite(entry,elen,1,stdout);
                printf(" (length %d)\n", elen);
            }
        }
        printf("\n");
