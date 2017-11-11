char *truncate_dll_name(char *path)
{
    /* Cut DLL name down to 8 characters after removing any mod_ prefix */
    char *tmppath = strdup(path);
    char *newname = strrchr(tmppath, '/') + 1;
    char *ext = strrchr(tmppath, '.');
    int len;

    if (ext == NULL)
        return tmppath;

    len = ext - newname;

    if (strncmp(newname, "mod_", 4) == 0) {
        strcpy(newname, newname + 4);
        len -= 4;
    }

    if (len > 8) {
        strcpy(newname + 8, strchr(newname, '.'));
    }

    return tmppath;
}