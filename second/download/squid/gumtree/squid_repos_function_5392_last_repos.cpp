void
Ftp::Gateway::hackShortcut(FTPSM * nextState)
{
    /* Clear some unwanted state */
    setCurrentOffset(0);
    restart_offset = 0;
    /* Save old error message & some state info */

    debugs(9, 3, HERE);

    if (old_request == NULL) {
        old_request = ctrl.last_command;
        ctrl.last_command = NULL;
        old_reply = ctrl.last_reply;
        ctrl.last_reply = NULL;

        if (pathcomps == NULL && filepath != NULL)
            old_filepath = xstrdup(filepath);
    }

    /* Jump to the "hack" state */
    nextState(this);
}