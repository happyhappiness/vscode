static const char *set_expiresbytype(cmd_parms *cmd, void *in_dir_config,
                                     const char *mime, const char *code)
{
    expires_dir_config *dir_config = in_dir_config;
    char *response, *real_code;
    const char *check;

    check = ap_strrchr_c(mime, '/');
    if ((strlen(++check) == 1) && (*check == '*')) {
        dir_config->wildcards = 1;
    }
    
    if ((response = check_code(cmd->pool, code, &real_code)) == NULL) {
        apr_table_setn(dir_config->expiresbytype, mime, real_code);
        return NULL;
    }
    return apr_pstrcat(cmd->pool,
                 "'ExpiresByType ", mime, " ", code, "': ", response, NULL);
}