static const char *configure_redirect(cmd_parms *cmd, void *d_, const char *arg1)
{
    dir_config_rec *d = d_;
    int status;

    if (!strcasecmp(arg1, "ON"))
        status = HTTP_MOVED_TEMPORARILY;
    else if (!strcasecmp(arg1, "OFF"))
        status = REDIRECT_OFF;
    else if (!strcasecmp(arg1, "permanent"))
        status = HTTP_MOVED_PERMANENTLY;
    else if (!strcasecmp(arg1, "temp"))
        status = HTTP_MOVED_TEMPORARILY;
    else if (!strcasecmp(arg1, "seeother"))
        status = HTTP_SEE_OTHER;
    else if (apr_isdigit(*arg1)) {
        status = atoi(arg1);
        if (!ap_is_HTTP_REDIRECT(status)) {
            return "DirectoryIndexRedirect only accepts values between 300 and 399";
        }
    }
    else {
        return "DirectoryIndexRedirect ON|OFF|permanent|temp|seeother|3xx";
    }

    d->redirect_index = status;
    return NULL;
}