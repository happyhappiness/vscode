    /* Set i to the first option argument. The previous one is the cursor. */
    i = (o == NULL) ? 2 : 3; /* Skip the key argument if needed. */

    /* Use sscanf because we need an *unsigned* long */
    rv = sscanf(c->argv[i-1]->ptr, "%lu", &cursor);
    if (rv != 1) {
        addReplyError(c, "invalid cursor");
        goto cleanup;
    }
