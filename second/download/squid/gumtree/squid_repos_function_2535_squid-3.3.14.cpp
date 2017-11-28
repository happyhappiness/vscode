static void
ftpReadCwd(FtpStateData * ftpState)
{
    int code = ftpState->ctrl.replycode;
    debugs(9, 3, HERE);

    if (code >= 200 && code < 300) {
        /* CWD OK */
        ftpState->unhack();

        /* Reset cwd_message to only include the last message */
        ftpState->cwd_message.reset("");
        for (wordlist *w = ftpState->ctrl.message; w; w = w->next) {
            ftpState->cwd_message.append(' ');
            ftpState->cwd_message.append(w->key);
        }
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