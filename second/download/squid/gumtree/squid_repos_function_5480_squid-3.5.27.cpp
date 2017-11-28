void
Ftp::Gateway::handleControlReply()
{
    Ftp::Client::handleControlReply();
    if (ctrl.message == NULL)
        return; // didn't get complete reply yet

    /* Copy the message except for the last line to cwd_message to be
     * printed in error messages.
     */
    for (wordlist *w = ctrl.message; w && w->next; w = w->next) {
        cwd_message.append('\n');
        cwd_message.append(w->key);
    }

    FTP_SM_FUNCS[state] (this);
}