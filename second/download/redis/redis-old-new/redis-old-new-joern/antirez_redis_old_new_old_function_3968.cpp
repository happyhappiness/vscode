int main(int argc, char **argv) {
    unsigned char *zl, *p, *entry;
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
        while ((p = ziplistNext(p, &entry, &elen)) != NULL) {
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
        while ((p = ziplistNext(p, &entry, &elen)) != NULL) {
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
        while ((p = ziplistNext(p, &entry, &elen)) != NULL) {
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
        if (ziplistNext(p, &entry, &elen) == NULL) {
            printf("No entry\n");
        } else {
            printf("ERROR\n");
        }
    }

    return 0;
}