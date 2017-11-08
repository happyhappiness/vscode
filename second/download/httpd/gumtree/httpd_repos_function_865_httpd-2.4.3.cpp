static const char *ssl_authz_verify_client_parse(cmd_parms *cmd,
                                                 const char *require_line,
                                                 const void **parsed)
{
    if (require_line && require_line[0])
        return "'Require ssl-verify-client' does not take arguments";

    return NULL;
}