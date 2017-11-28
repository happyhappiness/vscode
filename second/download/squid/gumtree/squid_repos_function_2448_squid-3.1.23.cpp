void
logfileRotate(Logfile * lf)
{
#ifdef S_ISREG

    struct stat sb;
#endif

    int i;
    char from[MAXPATHLEN];
    char to[MAXPATHLEN];
    assert(lf->path);

    if (lf->flags.syslog)
        return;

#ifdef S_ISREG

    if (stat(lf->path, &sb) == 0)
        if (S_ISREG(sb.st_mode) == 0)
            return;

#endif

    debugs(0, 1, "logfileRotate: " << lf->path);

    /* Rotate numbers 0 through N up one */
    for (i = Config.Log.rotateNumber; i > 1;) {
        i--;
        snprintf(from, MAXPATHLEN, "%s.%d", lf->path, i - 1);
        snprintf(to, MAXPATHLEN, "%s.%d", lf->path, i);
        xrename(from, to);
    }

    /* Rotate the current log to .0 */
    logfileFlush(lf);

    file_close(lf->fd);		/* always close */

    if (Config.Log.rotateNumber > 0) {
        snprintf(to, MAXPATHLEN, "%s.%d", lf->path, 0);
        xrename(lf->path, to);
    }

    /* Reopen the log.  It may have been renamed "manually" */
    lf->fd = file_open(lf->path, O_WRONLY | O_CREAT | O_TEXT);

    if (DISK_ERROR == lf->fd && lf->flags.fatal) {
        debugs(50, 1, "logfileRotate: " << lf->path << ": " << xstrerror());
        fatalf("Cannot open %s: %s", lf->path, xstrerror());
    }
}