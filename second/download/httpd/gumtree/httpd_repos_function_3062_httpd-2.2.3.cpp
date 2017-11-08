char * load_noinstall_path(const char *arg, int pathlen)
{
    char *newarg, *expanded_path;
    int newpathlen;

    newarg = (char *)malloc(strlen(arg) + 10);
    strcpy(newarg, arg);
    newarg[pathlen] = 0;

    newpathlen = pathlen;
    strcat(newarg, ".libs");
    newpathlen += sizeof(".libs") - 1;
    newarg[newpathlen] = 0;

#ifdef HAS_REALPATH
    expanded_path = malloc(PATH_MAX);
    expanded_path = realpath(newarg, expanded_path);
    /* Uh, oh.  There was an error.  Fall back on our first guess. */
    if (!expanded_path) {
        expanded_path = newarg;
    }
#else
    /* We might get ../ or something goofy.  Oh, well. */
    expanded_path = newarg;
#endif

    return expanded_path;
}