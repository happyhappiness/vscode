static const char *set_serv_tokens(cmd_parms *cmd, void *dummy,
                                   const char *arg1, const char *arg2)
{
    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    if (!strcasecmp(arg1, "OS")) {
        ap_server_tokens = SrvTk_OS;
    }
    else if (!strcasecmp(arg1, "Min") || !strcasecmp(arg1, "Minimal")) {
        ap_server_tokens = SrvTk_MINIMAL;
    }
    else if (!strcasecmp(arg1, "Major")) {
        ap_server_tokens = SrvTk_MAJOR;
    }
    else if (!strcasecmp(arg1, "Minor") ) {
        ap_server_tokens = SrvTk_MINOR;
    }
    else if (!strcasecmp(arg1, "Prod") || !strcasecmp(arg1, "ProductOnly")) {
        ap_server_tokens = SrvTk_PRODUCT_ONLY;
    }
    else if (!strcasecmp(arg1, "Full")) {
        ap_server_tokens = SrvTk_FULL;
    }
    else {
        return "ServerTokens takes 1 argument, 'Prod', 'Major', 'Minor', 'Min', 'OS', or 'Full'";
    }

    return NULL;
}