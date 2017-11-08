static void ap_add_module_commands(module *m, apr_pool_t *p)
{
    apr_pool_t *tpool;
    ap_mod_list *mln;
    const command_rec *cmd;
    char *dir;

    cmd = m->cmds;

    if (ap_config_hash == NULL) {
        rebuild_conf_hash(p, 0);
    }

    tpool = apr_hash_pool_get(ap_config_hash);

    while (cmd && cmd->name) {
        mln = apr_palloc(tpool, sizeof(ap_mod_list));
        mln->cmd = cmd;
        mln->m = m;
        dir = apr_pstrdup(tpool, cmd->name);

        ap_str_tolower(dir);

        mln->next = apr_hash_get(ap_config_hash, dir, APR_HASH_KEY_STRING);
        apr_hash_set(ap_config_hash, dir, APR_HASH_KEY_STRING, mln);
        ++cmd;
    }
}