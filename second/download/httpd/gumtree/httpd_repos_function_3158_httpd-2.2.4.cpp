static char *fixed_name(const char *fname, apr_pool_t *pool)
{
    char *semname;

    if (fname == NULL)
        semname = NULL;
    else {
        // Semaphores don't live in the file system, fix up the name
        while (*fname == '/' || *fname == '\\') {
            fname++;
        }

        semname = apr_pstrcat(pool, "/SEM32/", fname, NULL);

        if (semname[8] == ':') {
            semname[8] = '$';
        }
    }

    return semname;
}