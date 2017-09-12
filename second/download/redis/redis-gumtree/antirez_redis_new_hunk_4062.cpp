    {
        zl = createList();
        p = ziplistIndex(zl, 0);
        while (ziplistGet(p, &entry, &elen, &value)) {
            if (entry && strncmp("foo", entry, elen) == 0) {
                printf("Delete foo\n");
                zl = ziplistDelete(zl, &p);
            } else {
                printf("Entry: ");
                if (entry) {
                    fwrite(entry,elen,1,stdout);
                } else {
                    printf("%lld", value);
                }
                p = ziplistNext(p);
                printf("\n");
            }
        }
        printf("\n");
