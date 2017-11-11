static const char *add_charset_options(cmd_parms *cmd, void *in_dc, 
                                       const char *flag)
{
    charset_dir_t *dc = in_dc;

    if (!strcasecmp(flag, "ImplicitAdd")) {
        dc->implicit_add = IA_IMPADD;
    }
    else if (!strcasecmp(flag, "NoImplicitAdd")) {
        dc->implicit_add = IA_NOIMPADD;
    }
    else if (!strncasecmp(flag, "DebugLevel=", 11)) {
        dc->debug = atoi(flag + 11);
    }
    else {
        return apr_pstrcat(cmd->temp_pool, 
                           "Invalid CharsetOptions option: ",
                           flag,
                           NULL);
    }

    return NULL;
}