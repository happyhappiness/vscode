static const char *add_index(cmd_parms *cmd, void *dummy, const char *arg)
{
    dir_config_rec *d = dummy;

    if (!d->index_names) {
        d->index_names = apr_array_make(cmd->pool, 2, sizeof(char *));
    }
    *(const char **)apr_array_push(d->index_names) = arg;
    return NULL;
}