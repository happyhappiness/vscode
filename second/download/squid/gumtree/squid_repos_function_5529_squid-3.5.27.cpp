static void
ftpTrySlashHack(Ftp::Gateway * ftpState)
{
    char *path;
    ftpState->flags.try_slash_hack = 1;
    /* Free old paths */

    debugs(9, 3, HERE);

    if (ftpState->pathcomps)
        wordlistDestroy(&ftpState->pathcomps);

    safe_free(ftpState->filepath);

    /* Build the new path (urlpath begins with /) */
    path = xstrdup(ftpState->request->urlpath.termedBuf());

    rfc1738_unescape(path);

    ftpState->filepath = path;

    /* And off we go */
    ftpGetFile(ftpState);
}