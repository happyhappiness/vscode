static int
WIN32_create_key(void)
{
    int index;
    HKEY hKey;
    HKEY hKeyNext;
    int retval;
    LONG rv;

    hKey = HKEY_LOCAL_MACHINE;
    index = 0;
    retval = 0;

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

        /* Close the old key */
        rv = RegCloseKey(hKey);

        if (rv != ERROR_SUCCESS) {
            fprintf(stderr, "RegCloseKey %d\n", (int) rv);

            if (retval == 0) {
                /* Keep error status from RegCreateKeyEx, if any */
                retval = -4;
            }
        }

        if (retval) {
            break;
        }

        hKey = hKeyNext;
        index++;
    }

    if (keys[index] == NULL) {
        /* Close the final key we opened, if we walked the entire
         * tree
         */
        rv = RegCloseKey(hKey);

        if (rv != ERROR_SUCCESS) {
            fprintf(stderr, "RegCloseKey %d\n", (int) rv);

            if (retval == 0) {
                /* Keep error status from RegCreateKeyEx, if any */
                retval = -4;
            }
        }
    }

    return retval;
}