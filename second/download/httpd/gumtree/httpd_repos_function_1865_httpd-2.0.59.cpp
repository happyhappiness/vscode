static ap_filter_rec_t *register_filter(const char *name,
                            ap_filter_func filter_func,
                            ap_init_filter_func filter_init,
                            ap_filter_type ftype,
                            filter_trie_node **reg_filter_set)
{
    ap_filter_rec_t *frec;
    char *normalized_name;
    const char *n;
    filter_trie_node *node;

    if (!*reg_filter_set) {
        *reg_filter_set = trie_node_alloc(FILTER_POOL, NULL, 0);
    }

    normalized_name = apr_pstrdup(FILTER_POOL, name);
    ap_str_tolower(normalized_name);

    node = *reg_filter_set;
    for (n = normalized_name; *n; n++) {
        filter_trie_node *child = trie_node_alloc(FILTER_POOL, node, *n);
        if (apr_isalpha(*n)) {
            trie_node_link(FILTER_POOL, node, child, apr_toupper(*n));
        }
        node = child;
    }
    if (node->frec) {
        frec = node->frec;
    }
    else {
        frec = apr_palloc(FILTER_POOL, sizeof(*frec));
        node->frec = frec;
        frec->name = normalized_name;
    }
    frec->filter_func = filter_func;
    frec->filter_init_func = filter_init;
    frec->ftype = ftype;
    
    apr_pool_cleanup_register(FILTER_POOL, NULL, filter_cleanup, 
                              apr_pool_cleanup_null);
    return frec;
}