static void
logfile_mod_stdio_rotate(Logfile * lf)
{
#ifdef S_ISREG

    struct stat sb;
#endif

    int i;
    char from[MAXPATHLEN];
    char to[MAXPATHLEN];
    l_stdio_t *ll = (l_stdio_t *) lf->data;
    assert(lf->path);
    const char *realpath = lf->path+6; // skip 'stdio:' prefix.
    assert(realpath);

#ifdef S_ISREG

    if (stat(realpath, &sb) == 0)
        if (S_ISREG(sb.st_mode) == 0)
            return;

#endif

    debugs(0, DBG_IMPORTANT, "Rotate log file " << lf->path);

    /* Rotate numbers 0 through N up one */
    for (i = Config.Log.rotateNumber; i > 1;) {
        --i;
        snprintf(from, MAXPATHLEN, "%s.%d", realpath, i - 1);
        snprintf(to, MAXPATHLEN, "%s.%d", realpath, i);
        xrename(from, to);
    }

    /* Rotate the current log to .0 */
    logfileFlush(lf);

    file_close(ll->fd);		/* always close */

    if (Config.Log.rotateNumber > 0) {
        snprintf(to, MAXPATHLEN, "%s.%d", realpath, 0);
        xrename(realpath, to);
    }
    /* Reopen the log.  It may have been renamed "manually" */
    ll->fd = file_open(realpath, O_WRONLY | O_CREAT | O_TEXT);

    if (DISK_ERROR == ll->fd && lf->flags.fatal) {
        debugs(50, DBG_CRITICAL, "ERROR: logfileRotate: " << lf->path << ": " << xstrerror());
        fatalf("Cannot open %s: %s", lf->path, xstrerror());
    }
}