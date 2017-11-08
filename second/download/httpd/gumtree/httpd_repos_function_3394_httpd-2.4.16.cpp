static const char *set_serv_tokens(cmd_parms *cmd, void *dummy,
                                   const char *arg)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    if (!strcasecmp(arg, "OS")) {
        ap_server_tokens = SrvTk_OS;
    }
    else if (!strcasecmp(arg, "Min") || !strcasecmp(arg, "Minimal")) {
        ap_server_tokens = SrvTk_MINIMAL;
    }
    else if (!strcasecmp(arg, "Major")) {
        ap_server_tokens = SrvTk_MAJOR;
    }
    else if (!strcasecmp(arg, "Minor") ) {
        ap_server_tokens = SrvTk_MINOR;
    }
    else if (!strcasecmp(arg, "Prod") || !strcasecmp(arg, "ProductOnly")) {
        ap_server_tokens = SrvTk_PRODUCT_ONLY;
    }
    else if (!strcasecmp(arg, "Full")) {
        ap_server_tokens = SrvTk_FULL;
    }
    else {
        return "ServerTokens takes 1 argument: 'Prod(uctOnly)', 'Major', 'Minor', 'Min(imal)', 'OS', or 'Full'";
    }

    return NULL;
}