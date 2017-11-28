void SMB_Get_My_Name(char *name, int len)

{
    if (gethostname(name, len) < 0) { /* Error getting name */

        strncpy(name, "unknown", len);

        /* Should check the error */

#ifdef DEBUG
        fprintf(stderr, "gethostname in SMB_Get_My_Name returned error:");
        perror("");
#endif

    } else {
        char *address;
        /* only keep the portion up to the first "." */
        if (NULL != (address = strchr(name, '.'))) {
            *address = '\0';   /* truncate at first '.' */
        }
    }
}