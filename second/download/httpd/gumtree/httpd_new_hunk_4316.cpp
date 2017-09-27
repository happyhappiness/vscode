                APR_SIZE_T_FMT " bytes)\n", strlen(s));
        exit(1);
    }
    return ret;
}

/*
 * Similar to standard strstr() but we ignore case in this version.
 * Copied from ap_strcasestr().
 */
static char *xstrcasestr(const char *s1, const char *s2)
{
    char *p1, *p2;
    if (*s2 == '\0') {
        /* an empty s2 */
        return((char *)s1);
    }
    while(1) {
        for ( ; (*s1 != '\0') && (apr_tolower(*s1) != apr_tolower(*s2)); s1++);
        if (*s1 == '\0') {
            return(NULL);
        }
        /* found first character of s2, see if the rest matches */
        p1 = (char *)s1;
        p2 = (char *)s2;
        for (++p1, ++p2; apr_tolower(*p1) == apr_tolower(*p2); ++p1, ++p2) {
            if (*p1 == '\0') {
                /* both strings ended together */
                return((char *)s1);
            }
        }
        if (*p2 == '\0') {
            /* second string ended, a match */
            break;
        }
        /* didn't find a match here, try starting at next character in s1 */
        s1++;
    }
    return((char *)s1);
}

/* pool abort function */
static int abort_on_oom(int retcode)
{
    fprintf(stderr, "Could not allocate memory\n");
    exit(1);
    /* not reached */
