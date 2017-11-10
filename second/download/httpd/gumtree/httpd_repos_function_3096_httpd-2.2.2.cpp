char *nameof(char *fullpath)
{
    char buffer[1024];
    char *ext;
    char *name = strrchr(fullpath, '/');

    if (name == NULL) {
        name = strrchr(fullpath, '\\');
    }

    if (name == NULL) {
        name = fullpath;
    } else {
        name++;
    }

    strcpy(buffer, name);
    ext = strrchr(buffer, '.');

    if (ext) {
        *ext = 0;
        return strdup(buffer);
    }

    return name;
}