const struct h2_priority *h2_config_get_priority(const h2_config *conf, 
                                                 const char *content_type)
{
    if (content_type && conf->priorities) {
        size_t len = strcspn(content_type, "; \t");
        h2_priority *prio = apr_hash_get(conf->priorities, content_type, len);
        return prio? prio : apr_hash_get(conf->priorities, "*", 1);
    }
    return NULL;
}