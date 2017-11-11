static const char *set_crypto_driver(cmd_parms * cmd, void *config, const char *arg)
{
    session_crypto_conf *conf =
    (session_crypto_conf *)ap_get_module_config(cmd->server->module_config,
            &session_crypto_module);

    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);

    if (err != NULL) {
        return err;
    }

    conf->library = ap_getword_conf(cmd->pool, &arg);
    conf->params = arg;
    conf->library_set = 1;

    return NULL;
}