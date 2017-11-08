static const char *set_links(cmd_parms *cmd, void *CFG,
                             const char *elt, const char *att)
{
    apr_array_header_t *attrs;
    tattr *attr;
    proxy_html_conf *cfg = CFG;

    if (cfg->links == NULL)
        cfg->links = apr_hash_make(cmd->pool);

    attrs = apr_hash_get(cfg->links, elt, APR_HASH_KEY_STRING);
    if (!attrs) {
        attrs = apr_array_make(cmd->pool, 2, sizeof(tattr*));
        apr_hash_set(cfg->links, elt, APR_HASH_KEY_STRING, attrs);
    }
    attr = apr_array_push(attrs);
    attr->val = att;
    return NULL;
}