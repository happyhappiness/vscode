static const char *set_xbithack(cmd_parms *cmd, void *mconfig, const char *arg)
{
    include_dir_config *conf = mconfig;

    if (!strcasecmp(arg, "off")) {
        conf->xbithack = XBITHACK_OFF;
    }
    else if (!strcasecmp(arg, "on")) {
        conf->xbithack = XBITHACK_ON;
    }
    else if (!strcasecmp(arg, "full")) {
        conf->xbithack = XBITHACK_FULL;
    }
    else {
        return "XBitHack must be set to Off, On, or Full";
    }

    return NULL;
}