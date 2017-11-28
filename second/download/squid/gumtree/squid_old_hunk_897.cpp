
    /* Walk the tree, creating at each stage if necessary */

    while (keys[index]) {
        unsigned long result;
        rv = RegCreateKeyEx(hKey, keys[index],	/* subkey */
                            0,			/* reserved */
                            NULL,		/* class */
                            REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKeyNext, &result);

        if (rv != ERROR_SUCCESS) {
            fprintf(stderr, "RegCreateKeyEx(%s),%d\n", keys[index], (int) rv);
            retval = -4;
        }
