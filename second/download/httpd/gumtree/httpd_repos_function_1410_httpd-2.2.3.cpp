static char *get_path_param(apr_pool_t *pool, char *url,
                            const char *name)
{
    char *path = NULL;

    for (path = strstr(url, name); path; path = strstr(path + 1, name)) {
        path += strlen(name);
        if (*path == '=') {
            /*
             * Session path was found, get it's value
             */
            ++path;
            if (strlen(path)) {
                char *q;
                path = apr_pstrdup(pool, path);
                if ((q = strchr(path, '?')))
                    *q = '\0';
                return path;
            }
        }
    }
    return NULL;
}