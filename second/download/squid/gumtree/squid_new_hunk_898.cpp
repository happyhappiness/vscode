    if (rv != ERROR_SUCCESS) {
        fprintf(stderr, "RegOpenKeyEx HKLM\\%s, %d\n", REGKEY, (int) rv);
        return -4;
    }

    /* Now set the value and data */
    rv = RegSetValueEx(hKey, key,   /* value key name */
                       0,           /* reserved */
                       type,            /* type */
                       value,           /* value data */
                       (DWORD) value_size); /* for size of "value" */

    retval = 0;         /* Return value */

    if (rv != ERROR_SUCCESS) {
        fprintf(stderr, "RegQueryValueEx(key %s),%d\n", key, (int) rv);
        retval = -4;
    } else {
        fprintf(stderr, "Registry stored HKLM\\%s\\%s value %s\n",
