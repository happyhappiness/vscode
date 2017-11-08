apr_status_t filepath_compare_drive(const char *path1, const char *path2, apr_pool_t *p)
{
    char *s1, *s2;

    if (path1 && path2) {
        s1 = strchr (path1, ':');
        s2 = strchr (path2, ':');

        /* Make sure that they both have a drive/volume delimiter
            and are the same size.  Then see if they match.
        */
        if (s1 && s2 && ((s1-path1) == (s2-path2))) {
            return strnicmp (s1, s2, s1-path1);
        }
    }
    return -1;
}