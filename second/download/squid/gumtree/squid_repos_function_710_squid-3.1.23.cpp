static int
WIN32_StoreKey(const char *key, DWORD type, unsigned char *value,
               int value_size)
{
    LONG rv;
    HKEY hKey;
    int retval;

    rv = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REGKEY, 0, KEY_WRITE, &hKey);

    if (rv == ERROR_FILE_NOT_FOUND) {
        /* Key could not be opened -- try to create it
         */

        if (WIN32_create_key() < 0) {
            /* Creation failed (error already reported) */
            return -4;
        }

        /* Now it has been created we should be able to open it
         */
        rv = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REGKEY, 0, KEY_WRITE, &hKey);

        if (rv == ERROR_FILE_NOT_FOUND) {
            fprintf(stderr, "Registry does not contain key %s after creation\n",
                    REGKEY);
            return -1;
        }
    }

    if (rv != ERROR_SUCCESS) {
        fprintf(stderr, "RegOpenKeyEx HKLM\\%s, %d\n", REGKEY, (int) rv);
        return -4;
    }

    /* Now set the value and data */
    rv = RegSetValueEx(hKey, key,	/* value key name */
                       0,			/* reserved */
                       type,			/* type */
                       value,			/* value data */
                       (DWORD) value_size);	/* for size of "value" */

    retval = 0;			/* Return value */

    if (rv != ERROR_SUCCESS) {
        fprintf(stderr, "RegQueryValueEx(key %s),%d\n", key, (int) rv);
        retval = -4;
    } else {
        fprintf(stderr, "Registry stored HKLM\\%s\\%s value %s\n",
                REGKEY,
                key,
                type == REG_SZ ? value : (unsigned char *) "(not displayable)");
    }

    /* Make sure we close the key even if there was an error storing
     * the data
     */
    rv = RegCloseKey(hKey);

    if (rv != ERROR_SUCCESS) {
        fprintf(stderr, "RegCloseKey HKLM\\%s, %d\n", REGKEY, (int) rv);

        if (retval == 0) {
            /* Keep error status from RegQueryValueEx, if any */
            retval = -4;
        }
    }

    return retval;
}