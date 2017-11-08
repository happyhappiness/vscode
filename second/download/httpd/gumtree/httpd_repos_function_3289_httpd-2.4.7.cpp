static const char *set_enable_sendfile(cmd_parms *cmd, void *d_,
                                   const char *arg)
{
    core_dir_config *d = d_;

    if (strcasecmp(arg, "on") == 0) {
        d->enable_sendfile = ENABLE_SENDFILE_ON;
    }
    else if (strcasecmp(arg, "off") == 0) {
        d->enable_sendfile = ENABLE_SENDFILE_OFF;
    }
    else {
        return "parameter must be 'on' or 'off'";
    }

    return NULL;
}