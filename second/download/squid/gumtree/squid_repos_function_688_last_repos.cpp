void
_db_rotate_log(void)
{
    if (debug_log_file == NULL)
        return;

#ifdef S_ISREG
    struct stat sb;
    if (stat(debug_log_file, &sb) == 0)
        if (S_ISREG(sb.st_mode) == 0)
            return;
#endif

    char from[MAXPATHLEN];
    from[0] = '\0';

    char to[MAXPATHLEN];
    to[0] = '\0';

    /*
     * NOTE: we cannot use xrename here without having it in a
     * separate file -- tools.c has too many dependencies to be
     * used everywhere debug.c is used.
     */
    /* Rotate numbers 0 through N up one */
    for (int i = Debug::rotateNumber; i > 1;) {
        --i;
        snprintf(from, MAXPATHLEN, "%s.%d", debug_log_file, i - 1);
        snprintf(to, MAXPATHLEN, "%s.%d", debug_log_file, i);
#if _SQUID_WINDOWS_
        remove
        (to);
#endif
        errno = 0;
        if (rename(from, to) == -1) {
            const auto saved_errno = errno;
            debugs(0, DBG_IMPORTANT, "log rotation failed: " << xstrerr(saved_errno));
        }
    }

    /*
     * You can't rename open files on Microsoft "operating systems"
     * so we close before renaming.
     */
#if _SQUID_WINDOWS_
    if (debug_log != stderr)
        fclose(debug_log);
#endif
    /* Rotate the current log to .0 */
    if (Debug::rotateNumber > 0) {
        snprintf(to, MAXPATHLEN, "%s.%d", debug_log_file, 0);
#if _SQUID_WINDOWS_
        errno = 0;
        if (remove(to) == -1) {
            const auto saved_errno = errno;
            debugs(0, DBG_IMPORTANT, "removal of log file " << to << " failed: " << xstrerr(saved_errno));
        }
#endif
        errno = 0;
        if (rename(debug_log_file, to) == -1) {
            const auto saved_errno = errno;
            debugs(0, DBG_IMPORTANT, "renaming file " << debug_log_file << " to "
                   << to << "failed: " << xstrerr(saved_errno));
        }
    }

    /* Close and reopen the log.  It may have been renamed "manually"
     * before HUP'ing us. */
    if (debug_log != stderr)
        debugOpenLog(Debug::cache_log);
}