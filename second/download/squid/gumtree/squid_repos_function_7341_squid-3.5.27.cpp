int
main(void)
{
    hash_table *hid;
    LOCAL_ARRAY(char, buf, BUFSIZ);
    LOCAL_ARRAY(char, todelete, BUFSIZ);
    hash_link *walker = NULL;

    todelete[0] = '\0';
    printf("init\n");

    printf("creating hash table\n");
    if ((hid = hash_create((HASHCMP *) strcmp, 229, hash4)) < 0) {
        printf("hash_create error.\n");
        exit(1);
    }
    printf("done creating hash table: %d\n", hid);

    while (fgets(buf, BUFSIZ, stdin)) {
        buf[strlen(buf) - 1] = '\0';
        printf("Inserting '%s' for item %p to hash table: %d\n",
               buf, buf, hid);
        hash_insert(hid, xstrdup(buf), (void *) 0x12345678);
        if (random() % 17 == 0)
            strcpy(todelete, buf);
    }

    printf("walking hash table...\n");
    for (int i = 0, walker = hash_first(hid); walker; walker = hash_next(hid)) {
        printf("item %5d: key: '%s' item: %p\n", i++, walker->key,
               walker->item);
    }
    printf("done walking hash table...\n");

    if (todelete[0]) {
        printf("deleting %s from %d\n", todelete, hid);
        if (hash_delete(hid, todelete))
            printf("hash_delete error\n");
    }
    printf("walking hash table...\n");
    for (int i = 0, walker = hash_first(hid); walker; walker = hash_next(hid)) {
        printf("item %5d: key: '%s' item: %p\n", i++, walker->key,
               walker->item);
    }
    printf("done walking hash table...\n");

    printf("driver finished.\n");
    exit(0);
}