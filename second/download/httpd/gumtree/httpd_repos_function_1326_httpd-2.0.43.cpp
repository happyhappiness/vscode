static const char *set_xbithack(cmd_parms *cmd, void *xbp, const char *arg)
{
    include_dir_config *conf = (include_dir_config *)xbp;

    if (!strcasecmp(arg, "off")) {
        *conf->xbithack = xbithack_off;
    }
    else if (!strcasecmp(arg, "on")) {
        *conf->xbithack = xbithack_on;
    }
    else if (!strcasecmp(arg, "full")) {
        *conf->xbithack = xbithack_full;
    }
    else {
        return "XBitHack must be set to Off, On, or Full";
    }

    return NULL;
}