static void
ftpTraverseDirectory(Ftp::Gateway * ftpState)
{
    debugs(9, 4, HERE << (ftpState->filepath ? ftpState->filepath : "<NULL>"));

    safe_free(ftpState->dirpath);
    ftpState->dirpath = ftpState->filepath;
    ftpState->filepath = NULL;

    /* Done? */

    if (ftpState->pathcomps == NULL) {
        debugs(9, 3, HERE << "the final component was a directory");
        ftpListDir(ftpState);
        return;
    }

    /* Go to next path component */
    ftpState->filepath = wordlistChopHead(& ftpState->pathcomps);

    /* Check if we are to CWD or RETR */
    if (ftpState->pathcomps != NULL || ftpState->flags.isdir) {
        ftpSendCwd(ftpState);
    } else {
        debugs(9, 3, HERE << "final component is probably a file");
        ftpGetFile(ftpState);
        return;
    }
}