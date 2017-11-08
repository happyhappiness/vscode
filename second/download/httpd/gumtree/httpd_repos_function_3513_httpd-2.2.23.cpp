void add_rpath(count_chars *cc, const char *path)
{
    int size = 0;
    char *tmp;

#ifdef LINKER_FLAG_PREFIX
    size = strlen(LINKER_FLAG_PREFIX);
#endif
    size = size + strlen(path) + strlen(RPATH) + 2;
    tmp = malloc(size);
    if (tmp == NULL) {
        return;
    }
#ifdef LINKER_FLAG_PREFIX
    strcpy(tmp, LINKER_FLAG_PREFIX);
    strcat(tmp, RPATH);
#else
    strcpy(tmp, RPATH);
#endif
#ifndef LINKER_FLAG_NO_EQUALS
    strcat(tmp, "=");
#endif
    strcat(tmp, path);

    push_count_chars(cc, tmp);
}