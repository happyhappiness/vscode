    /* Set i to the first option argument. The previous one is the cursor. */
    i = (o == NULL) ? 2 : 3; /* Skip the key argument if needed. */

    /* Use strtoul() because we need an *unsigned* long, so
     * getLongLongFromObject() does not cover the whole cursor space. */
    errno = 0;
    cursor = strtoul(c->argv[i-1]->ptr, &eptr, 10);
    if (isspace(((char*)c->argv[i-1])[0]) || eptr[0] != '\0' || errno == ERANGE)
    {
        addReplyError(c, "invalid cursor");
        goto cleanup;
    }

    /* Step 1: Parse options. */
    while (i < c->argc) {
        j = c->argc - i;
