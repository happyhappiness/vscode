static void
rotate(const char *path, int rotate_count)
{
#ifdef S_ISREG
    struct stat sb;
#endif
    int i;
    char from[MAXPATHLEN];
    char to[MAXPATHLEN];
    assert(path);
#ifdef S_ISREG
    if (stat(path, &sb) == 0)
        if (S_ISREG(sb.st_mode) == 0)
            return;
#endif
    /* Rotate numbers 0 through N up one */
    for (i = rotate_count; i > 1;) {
        --i;
        snprintf(from, MAXPATHLEN, "%s.%d", path, i - 1);
        snprintf(to, MAXPATHLEN, "%s.%d", path, i);
#if _SQUID_OS2_ || _SQUID_WINDOWS_
        if (remove(to) < 0) {
            fprintf(stderr, "WARNING: remove '%s' failure: %s\n", to, xstrerror());
        }
#endif
        if (rename(from, to) < 0 && errno != ENOENT) {
            fprintf(stderr, "WARNING: rename '%s' to '%s' failure: %s\n", from, to, xstrerror());
        }
    }
    if (rotate_count > 0) {
        snprintf(to, MAXPATHLEN, "%s.%d", path, 0);
#if _SQUID_OS2_ || _SQUID_WINDOWS_
        if (remove(to) < 0) {
            fprintf(stderr, "WARNING: remove '%s' failure: %s\n", to, xstrerror());
        }
#endif
        if (rename(path, to) < 0 && errno != ENOENT) {
            fprintf(stderr, "WARNING: rename %s to %s failure: %s\n", path, to, xstrerror());
        }
    }
}