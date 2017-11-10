static const char *dav_cmd_davdepthinfinity(cmd_parms *cmd, void *config,
                                            int arg)
{
    dav_dir_conf *conf = (dav_dir_conf *)config;

    if (arg)
        conf->allow_depthinfinity = DAV_ENABLED_ON;
    else
        conf->allow_depthinfinity = DAV_ENABLED_OFF;
    return NULL;
}