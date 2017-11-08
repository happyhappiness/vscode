static const char *set_expiresactive(cmd_parms *cmd, void *in_dir_config, int arg)
{
    expires_dir_config *dir_config = in_dir_config;

    /* if we're here at all it's because someone explicitly
     * set the active flag
     */
    dir_config->active = ACTIVE_ON;
    if (arg == 0) {
        dir_config->active = ACTIVE_OFF;
    }
    return NULL;
}