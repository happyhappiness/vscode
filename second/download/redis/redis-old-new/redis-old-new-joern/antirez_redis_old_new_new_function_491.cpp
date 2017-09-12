static sds getDotfilePath(char *envoverride, char *dotfilename) {
    char *path = NULL;
    sds dotPath = NULL;

    /* Check the env for a dotfile override. */
    path = getenv(envoverride);
    if (path != NULL && *path != '\0') {
        if (!strcmp("/dev/null", path)) {
            return NULL;
        }

        /* If the env is set, return it. */
        dotPath = sdsnew(path);
    } else {
        char *home = getenv("HOME");
        if (home != NULL && *home != '\0') {
            /* If no override is set use $HOME/<dotfilename>. */
            dotPath = sdscatprintf(sdsempty(), "%s/%s", home, dotfilename);
        }
    }
    return dotPath;
}