static int
#if _SQUID_SOLARIS_
password_conversation(int num_msg, struct pam_message **msg, struct pam_response **resp, void *appdata_ptr)
#else
password_conversation(int num_msg, const struct pam_message **msg, struct pam_response **resp, void *appdata_ptr)
#endif
{
    if (num_msg != 1 || msg[0]->msg_style != PAM_PROMPT_ECHO_OFF) {
        fprintf(stderr, "ERROR: Unexpected PAM converstaion '%d/%s'\n", msg[0]->msg_style, msg[0]->msg);
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
        fprintf(stderr, "ERROR: No password available to password_converstation!\n");
        return PAM_CONV_ERR;
    }
    *resp = (struct pam_response *)(calloc(num_msg, sizeof(struct pam_response)));
    if (!*resp) {
        fprintf(stderr, "ERROR: Out of memory!\n");
        return PAM_CONV_ERR;
    }
    (*resp)[0].resp = strdup((char *) appdata_ptr);
    (*resp)[0].resp_retcode = 0;

    return ((*resp)[0].resp ? PAM_SUCCESS : PAM_CONV_ERR);
}