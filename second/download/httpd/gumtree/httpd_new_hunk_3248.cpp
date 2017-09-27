        *current = ap_add_node(curr_parent, *current, newdir, 0);
    }

    return retval;
}

#define VARBUF_INIT_LEN 200
#define VARBUF_MAX_LEN  (16*1024*1024)

AP_DECLARE(const char *) ap_build_cont_config(apr_pool_t *p,
                                              apr_pool_t *temp_pool,
                                              cmd_parms *parms,
                                              ap_directive_t **current,
                                              ap_directive_t **curr_parent,
                                              char *orig_directive)
{
    char *bracket;
    const char *retval;
    ap_directive_t *sub_tree = NULL;
    apr_status_t rc;
    struct ap_varbuf vb;
    apr_size_t max_len = VARBUF_MAX_LEN;
    if (p == temp_pool)
        max_len = HUGE_STRING_LEN; /* lower limit for .htaccess */

    bracket = apr_pstrcat(temp_pool, orig_directive + 1, ">", NULL);
    ap_varbuf_init(temp_pool, &vb, VARBUF_INIT_LEN);

    while ((rc = ap_varbuf_cfg_getline(&vb, parms->config_file, max_len))
           == APR_SUCCESS) {
        if (!memcmp(vb.buf, "</", 2)
            && (strcasecmp(vb.buf + 2, bracket) == 0)
            && (*curr_parent == NULL)) {
            break;
        }
        retval = ap_build_config_sub(p, temp_pool, vb.buf, parms, current,
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
    ap_varbuf_free(&vb);
    if (rc != APR_EOF && rc != APR_SUCCESS)
        return ap_pcfg_strerror(temp_pool, parms->config_file, rc);

    *current = sub_tree;
    return NULL;
}

static const char *ap_walk_config_sub(const ap_directive_t *current,
                                      cmd_parms *parms,
                                      ap_conf_vector_t *section_vector)
{
    const command_rec *cmd;
    ap_mod_list *ml;
    char *dir = apr_pstrdup(parms->temp_pool, current->directive);

    ap_str_tolower(dir);

    ml = apr_hash_get(ap_config_hash, dir, APR_HASH_KEY_STRING);

    if (ml == NULL) {
        parms->err_directive = current;
        if (parms->override & NONFATAL_UNKNOWN) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, parms->temp_pool,
                          APLOGNO(02296) "Unknown directive %s "
                          "perhaps misspelled or defined by a module "
                          "not included in the server configuration", dir);
            return NULL;
        }
        else {
            return apr_pstrcat(parms->pool, "Invalid command '",
                               current->directive,
                               "', perhaps misspelled or defined by a module "
                               "not included in the server configuration",
                               NULL);
        }
    }

    for ( ; ml != NULL; ml = ml->next) {
        void *dir_config = ap_set_config_vectors(parms->server,
                                                 section_vector,
                                                 parms->path,
