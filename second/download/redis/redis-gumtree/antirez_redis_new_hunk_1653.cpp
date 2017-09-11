    zl = pop(zl,ZIPLIST_TAIL);
    ziplistRepr(zl);

    zfree(zl);

    printf("Get element at index 3:\n");
    {
        zl = createList();
