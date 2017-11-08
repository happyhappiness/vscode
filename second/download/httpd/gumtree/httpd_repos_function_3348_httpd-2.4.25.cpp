static const char *set_trusted_certs(cmd_parms *cmd, void *dummy, char *arg)
{
    char **ptr = (char **)apr_array_push(certlist);

    *ptr = arg;
    return NULL;
}