apr_status_t filepath_has_drive(const char *rootpath, int only, apr_pool_t *p)
{
    char *s;

    if (rootpath) {
        s = strchr (rootpath, ':');
        if (only)
            /* Test if the path only has a drive/volume and nothing else
            */
            return (s && (s != rootpath) && !s[1]);
        else
            /* Test if the path includes a drive/volume
            */
            return (s && (s != rootpath));
    }
    return 0;
}