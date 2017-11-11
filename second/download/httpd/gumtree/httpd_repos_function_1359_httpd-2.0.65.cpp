static int is_only_below(const char *path)
{
#ifdef HAVE_DRIVE_LETTERS
    if (path[1] == ':') 
        return 0;
#endif
#ifdef NETWARE
    if (ap_strchr_c(path, ':'))
        return 0;
#endif
    if (path[0] == '/') {
        return 0;
    }
    while (*path) {
        int dots = 0;
        while (path[dots] == '.')
            ++dots;
#if defined(WIN32) 
        /* If the name is canonical this is redundant
         * but in security, redundancy is worthwhile.
         * Does OS2 belong here (accepts ... for ..)?
         */
        if (dots > 1 && (!path[dots] || path[dots] == '/'))
            return 0;
#else
        if (dots == 2 && (!path[dots] || path[dots] == '/'))
            return 0;
#endif
        path += dots;
        /* Advance to either the null byte at the end of the
         * string or the character right after the next slash,
         * whichever comes first
         */
        while (*path && (*path++ != '/')) {
            continue;
        }
    }
    return 1;
}