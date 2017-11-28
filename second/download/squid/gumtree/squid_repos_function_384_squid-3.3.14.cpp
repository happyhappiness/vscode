void
Check_forfilechange(usersfile * uf)
{
    struct stat ChkBuf;		/* Stat data buffer */

    /* Stat the allowed users file. If it cannot be accessed, return. */

    if (uf->path == NULL)
        return;

    if (stat(uf->path, &ChkBuf) < 0) {
        if (errno == ENOENT) {
            uf->LMT = 0;
            free_names(uf);
        } else {		/* Report error when accessing file */
            syslog(LOG_ERR, "%s: %s", uf->path, strerror(errno));
        }
        return;
    }
    /* return if no change */
    if (ChkBuf.st_mtime == uf->LMT)
        return;

    /*
     * The file changed, so re-read it.
     */
    syslog(LOG_INFO, "Check_forfilechange: Reloading user list '%s'.", uf->path);
    Read_usersfile(NULL, uf);
}