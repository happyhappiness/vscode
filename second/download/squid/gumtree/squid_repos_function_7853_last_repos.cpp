char *
xstrdup(const char *s)
{
    if (!s) {
        if (failure_notify) {
            (*failure_notify) ("xstrdup: tried to dup a NULL pointer!\n");
        } else {
            errno = EINVAL;
            perror("xstrdup: tried to dup a NULL pointer!");
        }
        exit(1);
    }

    /* copy string, including terminating character */
    size_t sz = strlen(s) + 1;
    char *p = static_cast<char *>(xmalloc(sz));
    memcpy(p, s, sz);

    return p;
}