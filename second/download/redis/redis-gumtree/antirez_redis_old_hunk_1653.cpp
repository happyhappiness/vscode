    zl = pop(zl,ZIPLIST_TAIL);
    ziplistRepr(zl);

    printf("Get element at index 3:\n");
    {
        zl = createList();
