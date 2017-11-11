static const char *scgi_set_send_file(cmd_parms *cmd, void *mconfig,
                                      const char *arg)
{
    scgi_config *conf=mconfig;

    if (!strcasecmp(arg, "Off")) {
        conf->sendfile = scgi_sendfile_off;
    }
    else if (!strcasecmp(arg, "On")) {
        conf->sendfile = scgi_sendfile_on;
    }
    else {
        conf->sendfile = arg;
    }
    return NULL;
}