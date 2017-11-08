static char *get_path_param(apr_pool_t *pool, char *url,
                            const char *name, int scolon_sep)
{
    char *path = NULL;
    char *pathdelims = "?&";

    if (scolon_sep) {
        pathdelims = ";?&";
    }
    for (path = strstr(url, name); path; path = strstr(path + 1, name)) {
        path += strlen(name);
        if (*path == '=') {
            /*
             * Session path was found, get it's value
             */
            ++path;
            if (strlen(path)) {
                char *q;
                path = apr_strtok(apr_pstrdup(pool, path), pathdelims, &q);
                return path;
            }
        }
    }
    return NULL;
}