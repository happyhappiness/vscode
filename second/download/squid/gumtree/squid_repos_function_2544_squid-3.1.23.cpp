static void
ftpReadCwd(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (code >= 200 && code < 300) {
        /* CWD OK */
        ftpState->unhack();
        /* Reset cwd_message to only include the last message */

        if (ftpState->cwd_message)
            wordlistDestroy(&ftpState->cwd_message);

        ftpState->cwd_message = ftpState->ctrl.message;

        ftpState->ctrl.message = NULL;

        /* Continue to traverse the path */
        ftpTraverseDirectory(ftpState);
    } else {
        /* CWD FAILED */

        if (!ftpState->flags.put)
            ftpFail(ftpState);
        else
            ftpSendMkdir(ftpState);
    }
}