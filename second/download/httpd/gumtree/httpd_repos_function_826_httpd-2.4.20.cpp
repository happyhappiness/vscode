static const char *ssl_cmd_crlcheck_parse(cmd_parms *parms,
                                          const char *arg,
                                          ssl_crlcheck_t *mode)
{
    if (strcEQ(arg, "none")) {
        *mode = SSL_CRLCHECK_NONE;
    }
    else if (strcEQ(arg, "leaf")) {
        *mode = SSL_CRLCHECK_LEAF;
    }
    else if (strcEQ(arg, "chain")) {
        *mode = SSL_CRLCHECK_CHAIN;
    }
    else {
        return apr_pstrcat(parms->temp_pool, parms->cmd->name,
                           ": Invalid argument '", arg, "'",
                           NULL);
    }

    return NULL;
}