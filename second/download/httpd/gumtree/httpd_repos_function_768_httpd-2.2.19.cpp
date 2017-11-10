static const char *ssl_cmd_check_dir(cmd_parms *parms,
                                     const char **dir)
{
    const char *dirpath = ap_server_root_relative(parms->pool, *dir);

    if (!dirpath) {
        return apr_pstrcat(parms->pool, parms->cmd->name,
                           ": Invalid dir path ", *dir, NULL);
    }
    *dir = dirpath;

    if (ssl_util_path_check(SSL_FLAGS_CHECK_DIR, *dir, parms->pool)) {
        return NULL;
    }

    return apr_pstrcat(parms->pool, parms->cmd->name,
                       ": directory '", *dir,
                       "' does not exist", NULL);

}