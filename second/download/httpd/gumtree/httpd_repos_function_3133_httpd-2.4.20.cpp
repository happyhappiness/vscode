static const char *set_crypto_passphrase_file(cmd_parms *cmd, void *config,
                                  const char *filename)
{
    char buffer[MAX_STRING_LEN];
    char *arg;
    const char *args;
    ap_configfile_t *file;
    apr_status_t rv;

    filename = ap_server_root_relative(cmd->temp_pool, filename);
    rv = ap_pcfg_openfile(&file, cmd->temp_pool, filename);
    if (rv != APR_SUCCESS) {
        return apr_psprintf(cmd->pool, "%s: Could not open file %s: %pm",
                            cmd->cmd->name, filename, &rv);
    }

    while (!(ap_cfg_getline(buffer, sizeof(buffer), file))) {
        args = buffer;
        while (*(arg = ap_getword_conf(cmd->pool, &args)) != '\0') {
            if (*arg == '#') {
                break;
            }
            set_crypto_passphrase(cmd, config, arg);
        }
    }

    ap_cfg_closefile(file);

    return NULL;
}