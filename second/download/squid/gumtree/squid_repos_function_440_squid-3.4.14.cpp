int
password_conversation(int num_msg, PAM_CONV_FUNC_CONST_PARM struct pam_message **msg, struct pam_response **resp, void *appdata_ptr)
{
    if (num_msg != 1 || msg[0]->msg_style != PAM_PROMPT_ECHO_OFF) {
        debug("ERROR: Unexpected PAM converstaion '%d/%s'\n", msg[0]->msg_style, msg[0]->msg);
        return PAM_CONV_ERR;
    }
#if _SQUID_SOLARIS_
    if (!appdata_ptr) {
        /* Workaround for Solaris 2.6 where the PAM library is broken
         * and does not pass appdata_ptr to the conversation routine
         */
        appdata_ptr = password;
    }
#endif
    if (!appdata_ptr) {
        debug("ERROR: No password available to password_converstation!\n");
        return PAM_CONV_ERR;
    }
    *resp = static_cast<struct pam_response *>(calloc(num_msg, sizeof(struct pam_response)));
    if (!*resp) {
        debug("ERROR: Out of memory!\n");
        return PAM_CONV_ERR;
    }
    (*resp)[0].resp = xstrdup((char *) appdata_ptr);
    (*resp)[0].resp_retcode = 0;

    return ((*resp)[0].resp ? PAM_SUCCESS : PAM_CONV_ERR);
}