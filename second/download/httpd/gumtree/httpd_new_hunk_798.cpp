
        apr_hook_debug_current = m->name;
        m->register_hooks(p);
    }
}

static void ap_add_module_commands(module *m, apr_pool_t *p);

typedef struct ap_mod_list_struct ap_mod_list;
struct ap_mod_list_struct {
    struct ap_mod_list_struct *next;
    module *m;
    const command_rec *cmd;
};

static apr_status_t reload_conf_hash(void *baton)
{
    ap_config_hash = NULL;
    return APR_SUCCESS;
}

static void rebuild_conf_hash(apr_pool_t *p, int add_prelinked)
{
    module **m;

    ap_config_hash = apr_hash_make(p);

    apr_pool_cleanup_register(p, NULL, reload_conf_hash,
                              apr_pool_cleanup_null);
    if (add_prelinked) {
        for (m = ap_prelinked_modules; *m != NULL; m++) {
            ap_add_module_commands(*m, p);
        }
    }
}

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


/* One-time setup for precompiled modules --- NOT to be done on restart */

AP_DECLARE(const char *) ap_add_module(module *m, apr_pool_t *p)
{
    /* This could be called from a LoadModule httpd.conf command,
     * after the file has been linked and the module structure within it
     * teased out...
     */

    if (m->version != MODULE_MAGIC_NUMBER_MAJOR) {
        return apr_psprintf(p, "Module \"%s\" is not compatible with this "
                            "version of Apache (found %d, need %d). Please "
                            "contact the vendor for the correct version.",
                            m->name, m->version, MODULE_MAGIC_NUMBER_MAJOR);
    }

    if (m->next == NULL) {
        m->next = ap_top_module;
        ap_top_module = m;
    }

    if (m->module_index == -1) {
        m->module_index = total_modules++;
        dynamic_modules++;

        if (dynamic_modules > DYNAMIC_MODULE_LIMIT) {
            return apr_psprintf(p, "Module \"%s\" could not be loaded, "
                                "because the dynamic module limit was "
                                "reached. Please increase "
                                "DYNAMIC_MODULE_LIMIT and recompile.", m->name);
        }
    }

    /* Some C compilers put a complete path into __FILE__, but we want
     * only the filename (e.g. mod_includes.c). So check for path
     * components (Unix and DOS), and remove them.
