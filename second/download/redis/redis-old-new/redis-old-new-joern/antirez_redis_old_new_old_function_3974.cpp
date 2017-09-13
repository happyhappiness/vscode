int main(int argc, char **argv) {
    unsigned char *zl, *p;
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
        while ((p = ziplistNext(p, &s)) != NULL) {
            printf("Entry: %s (length %ld)\n", s, sdslen(s));
        }
        printf("\n");
    }

    printf("Iterate list from 1 to end:\n");
    {
        zl = createList();
        p = ziplistIndex(zl, 1);
        while ((p = ziplistNext(p, &s)) != NULL) {
            printf("Entry: %s (length %ld)\n", s, sdslen(s));
        }
        printf("\n");
    }

    printf("Iterate list from 2 to end:\n");
    {
        zl = createList();
        p = ziplistIndex(zl, 2);
        while ((p = ziplistNext(p, &s)) != NULL) {
            printf("Entry: %s (length %ld)\n", s, sdslen(s));
        }
        printf("\n");
    }

    printf("Iterate starting out of range:\n");
    {
        zl = createList();
        p = ziplistIndex(zl, 3);
        if (ziplistNext(p, &s) == NULL) {
            printf("No entry\n");
        } else {
            printf("ERROR\n");
        }
    }

    return 0;
}