static const char *set_expiresdefault(cmd_parms *cmd, void *in_dir_config,
                                      const char *code)
{
    expires_dir_config * dir_config = in_dir_config;
    char *response, *real_code;

    if ((response = check_code(cmd->pool, code, &real_code)) == NULL) {
        dir_config->expiresdefault = real_code;
        return NULL;
    }
    return apr_pstrcat(cmd->pool,
                   "'ExpiresDefault ", code, "': ", response, NULL);
}