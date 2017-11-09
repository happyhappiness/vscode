static const char *cmd_servertype(cmd_parms *cmd, void *in_dconf,
                                   const char *val)
{
    fcgi_dirconf_t *dconf = in_dconf;

    if (!strcasecmp(val, "GENERIC")) {
       dconf->backend_type = BACKEND_GENERIC;
    }
    else if (!strcasecmp(val, "FPM")) {
       dconf->backend_type = BACKEND_FPM;
    }
    else {
        return "ProxyFCGIBackendType requires one of the following arguments: "
               "'GENERIC', 'FPM'";
    }

    return NULL;
}