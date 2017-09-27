        *current = ap_add_node(curr_parent, *current, newdir, 0);
    }

    return retval;
}

AP_DECLARE(const char *) ap_build_cont_config(apr_pool_t *p,
                                              apr_pool_t *temp_pool,
                                              cmd_parms *parms,
                                              ap_directive_t **current,
                                              ap_directive_t **curr_parent,
                                              char *orig_directive)
{
    char *l;
    char *bracket;
    const char *retval;
    ap_directive_t *sub_tree = NULL;

    /* Since this function can be called recursively, allocate
     * the temporary 8k string buffer from the temp_pool rather
     * than the stack to avoid over-running a fixed length stack.
     */
    l = apr_palloc(temp_pool, MAX_STRING_LEN);

    bracket = apr_pstrcat(p, orig_directive + 1, ">", NULL);
    while (!(ap_cfg_getline(l, MAX_STRING_LEN, parms->config_file))) {
        if (!memcmp(l, "</", 2)
            && (strcasecmp(l + 2, bracket) == 0)
            && (*curr_parent == NULL)) {
            break;
        }
        retval = ap_build_config_sub(p, temp_pool, l, parms, current,
                                     curr_parent, &sub_tree);
        if (retval != NULL)
            return retval;

        if (sub_tree == NULL) {
            sub_tree = *curr_parent;
        }

        if (sub_tree == NULL) {
            sub_tree = *current;
        }
    }

    *current = sub_tree;
    return NULL;
}

static const char *ap_walk_config_sub(const ap_directive_t *current,
                                      cmd_parms *parms,
                                      ap_conf_vector_t *section_vector)
{
    const command_rec *cmd;
    ap_mod_list *ml;
    char *dir = apr_pstrdup(parms->pool, current->directive);

    ap_str_tolower(dir);

    ml = apr_hash_get(ap_config_hash, dir, APR_HASH_KEY_STRING);

    if (ml == NULL) {
        parms->err_directive = current;
        return apr_pstrcat(parms->pool, "Invalid command '",
                           current->directive,
                           "', perhaps misspelled or defined by a module "
                           "not included in the server configuration",
                           NULL);
    }

    for ( ; ml != NULL; ml = ml->next) {
        void *dir_config = ap_set_config_vectors(parms->server,
                                                 section_vector,
                                                 parms->path,
