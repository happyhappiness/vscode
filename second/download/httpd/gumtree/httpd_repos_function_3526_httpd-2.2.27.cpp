char * load_install_path(const char *arg)
{
    FILE *f;
    char *path;

    path = malloc(PATH_MAX);

    f = fopen(arg,"r");
    if (f == NULL) {
        return NULL;
    }
    fgets(path, PATH_MAX, f);
    fclose(f);
    if (path[strlen(path)-1] == '\n') {
        path[strlen(path)-1] = '\0';
    }
    /* Check that we have an absolute path.
     * Otherwise the file could be a GNU libtool file.
     */
    if (path[0] != '/') {
        return NULL;
    }
    return path;
}