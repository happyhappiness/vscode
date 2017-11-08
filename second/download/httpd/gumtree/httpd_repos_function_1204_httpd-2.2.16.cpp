static const char *set_language_priority(cmd_parms *cmd, void *n_,
                                         const char *lang)
{
    neg_dir_config *n = n_;
    const char **langp;

    if (!n->language_priority)
        n->language_priority = apr_array_make(cmd->pool, 4, sizeof(char *));

    langp = (const char **) apr_array_push(n->language_priority);
    *langp = lang;
    return NULL;
}