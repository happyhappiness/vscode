    if (stat(path, &sb) == 0)
        if (S_ISREG(sb.st_mode) == 0)
            return;
#endif
    /* Rotate numbers 0 through N up one */
    for (i = rotate_count; i > 1;) {
        i--;
        snprintf(from, MAXPATHLEN, "%s.%d", path, i - 1);
        snprintf(to, MAXPATHLEN, "%s.%d", path, i);
#if _SQUID_OS2_ || _SQUID_WINDOWS_
        if (remove(to) < 0) {
            fprintf(stderr, "WARNING: remove '%s' failure: %s\n", to, xstrerror());
        }
