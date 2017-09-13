int main(int argc, char **argv) {
    unsigned char *zl, *p, *q, *entry;
    unsigned int elen;
    sds s;

    zl = createList();
    ziplistRepr(zl);

    zl = ziplistPop(zl, &s, ZIPLIST_TAIL);
    printf("Pop tail: %s (length %ld)\n", s, sdslen(s));
    ziplistRepr(zl);

    zl = ziplistPop(zl, &s, ZIPLIST_HEAD);
    printf("Pop head: %s (length %ld)\n", s, sdslen(s));
    ziplistRepr(zl);

    printf("Iterate list from 0 to end:\n");
    {
        zl = createList();
        p = ziplistIndex(zl, 0);
        while ((p = ziplistNext(p, NULL, &entry, &elen)) != NULL) {
            printf("Entry: ");
            fwrite(entry,elen,1,stdout);
            printf(" (length %d)\n", elen);
        }
        printf("\n");
    }

    printf("Iterate list from 1 to end:\n");
    {
        zl = createList();
        p = ziplistIndex(zl, 1);
        while ((p = ziplistNext(p, NULL, &entry, &elen)) != NULL) {
            printf("Entry: ");
            fwrite(entry,elen,1,stdout);
            printf(" (length %d)\n", elen);
        }
        printf("\n");
    }

    printf("Iterate list from 2 to end:\n");
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
        }
        printf("\n");
    }

    printf("Delete inclusive range 0,0:\n");
    {
        zl = createList();
        zl = ziplistDeleteRange(zl, 0, 1);
        ziplistRepr(zl);
    }

    printf("Delete inclusive range 0,1:\n");
    {
        zl = createList();
        zl = ziplistDeleteRange(zl, 0, 2);
        ziplistRepr(zl);
    }

    printf("Delete inclusive range 1,2:\n");
    {
        zl = createList();
        zl = ziplistDeleteRange(zl, 1, 2);
        ziplistRepr(zl);
    }

    printf("Delete with start index out of range:\n");
    {
        zl = createList();
        zl = ziplistDeleteRange(zl, 5, 1);
        ziplistRepr(zl);
    }

    printf("Delete with num overflow:\n");
    {
        zl = createList();
        zl = ziplistDeleteRange(zl, 1, 5);
        ziplistRepr(zl);
    }

    printf("Delete foo while iterating:\n");
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
        ziplistRepr(zl);
        printf("\n");
    }

    return 0;
}