}

static const char *set_access_name(cmd_parms *cmd, void *dummy,
                                   const char *arg)
{
    void *sconf = cmd->server->module_config;
    core_server_config *conf = ap_get_core_module_config(sconf);

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE);
    if (err != NULL) {
        return err;
    }

    conf->access_name = apr_pstrdup(cmd->pool, arg);
    return NULL;
}

AP_DECLARE(const char *) ap_resolve_env(apr_pool_t *p, const char * word)
{
# define SMALL_EXPANSION 5
    struct sll {
        struct sll *next;
        const char *string;
        apr_size_t len;
    } *result, *current, sresult[SMALL_EXPANSION];
    char *res_buf, *cp;
    const char *s, *e, *ep;
    unsigned spc;
    apr_size_t outlen;

    s = ap_strchr_c(word, '$');
    if (!s) {
        return word;
    }

    /* well, actually something to do */
    ep = word + strlen(word);
    spc = 0;
    result = current = &(sresult[spc++]);
    current->next = NULL;
    current->string = word;
    current->len = s - word;
    outlen = current->len;

    do {
        /* prepare next entry */
        if (current->len) {
            current->next = (spc < SMALL_EXPANSION)
                            ? &(sresult[spc++])
                            : (struct sll *)apr_palloc(p,
                                                       sizeof(*current->next));
            current = current->next;
            current->next = NULL;
            current->len = 0;
        }

        if (*s == '$') {
            if (s[1] == '{' && (e = ap_strchr_c(s, '}'))) {
                char *name = apr_pstrndup(p, s+2, e-s-2);
                word = NULL;
                if (server_config_defined_vars)
                    word = apr_table_get(server_config_defined_vars, name);
                if (!word)
                    word = getenv(name);
                if (word) {
                    current->string = word;
                    current->len = strlen(word);
                    outlen += current->len;
                }
                else {
                    if (ap_strchr(name, ':') == 0)
                        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL, APLOGNO(00111)
                                     "Config variable ${%s} is not defined",
                                     name);
                    current->string = s;
                    current->len = e - s + 1;
                    outlen += current->len;
                }
                s = e + 1;
            }
            else {
                current->string = s++;
                current->len = 1;
                ++outlen;
            }
        }
        else {
            word = s;
            s = ap_strchr_c(s, '$');
            current->string = word;
            current->len = s ? s - word : ep - word;
            outlen += current->len;
        }
    } while (s && *s);

    /* assemble result */
    res_buf = cp = apr_palloc(p, outlen + 1);
    do {
        if (result->len) {
            memcpy(cp, result->string, result->len);
            cp += result->len;
        }
        result = result->next;
    } while (result);
    res_buf[outlen] = '\0';

    return res_buf;
}

static int reset_config_defines(void *dummy)
{
    ap_server_config_defines = saved_server_config_defines;
    server_config_defined_vars = NULL;
    return OK;
}

/*
 * Make sure we can revert the effects of Define/UnDefine when restarting.
 * This function must be called once per loading of the config, before
 * ap_server_config_defines is changed. This may be during reading of the
 * config, which is even before the pre_config hook is run (due to
 * EXEC_ON_READ for Define/UnDefine).
 */
static void init_config_defines(apr_pool_t *pconf)
{
    saved_server_config_defines = ap_server_config_defines;
    /* Use apr_array_copy instead of apr_array_copy_hdr because it does not
     * protect from the way unset_define removes entries.
     */
    ap_server_config_defines = apr_array_copy(pconf, ap_server_config_defines);
}

static const char *set_define(cmd_parms *cmd, void *dummy,
                              const char *name, const char *value)
{
    const char *err = ap_check_cmd_context(cmd, NOT_IN_HTACCESS);
    if (err)
        return err;
    if (ap_strchr_c(name, ':') != NULL)
        return "Variable name must not contain ':'";

    if (!saved_server_config_defines)
        init_config_defines(cmd->pool);
    if (!ap_exists_config_define(name)) {
        char **newv = (char **)apr_array_push(ap_server_config_defines);
        *newv = apr_pstrdup(cmd->pool, name);
    }
    if (value) {
        if (!server_config_defined_vars)
            server_config_defined_vars = apr_table_make(cmd->pool, 5);
        apr_table_setn(server_config_defined_vars, name, value);
    }

    return NULL;
}

static const char *unset_define(cmd_parms *cmd, void *dummy,
                                const char *name)
{
    int i;
    char **defines;
    const char *err = ap_check_cmd_context(cmd, NOT_IN_HTACCESS);
    if (err)
        return err;
    if (ap_strchr_c(name, ':') != NULL)
        return "Variable name must not contain ':'";

    if (!saved_server_config_defines)
        init_config_defines(cmd->pool);

    defines = (char **)ap_server_config_defines->elts;
    for (i = 0; i < ap_server_config_defines->nelts; i++) {
        if (strcmp(defines[i], name) == 0) {
            defines[i] = apr_array_pop(ap_server_config_defines);
            break;
        }
    }

    if (server_config_defined_vars) {
        apr_table_unset(server_config_defined_vars, name);
    }

    return NULL;
}

static const char *generate_error(cmd_parms *cmd, void *dummy,
                                  const char *arg)
{
    if (!arg || !*arg) {
        return "The Error directive was used with no message.";
    }

    if (*arg == '"' || *arg == '\'') { /* strip off quotes */
        apr_size_t len = strlen(arg);
        char last = *(arg + len - 1);

        if (*arg == last) {
            return apr_pstrndup(cmd->pool, arg + 1, len - 2);
        }
    }

    return arg;
}

#ifdef GPROF
static const char *set_gprof_dir(cmd_parms *cmd, void *dummy, const char *arg)
{
    void *sconf = cmd->server->module_config;
    core_server_config *conf = ap_get_core_module_config(sconf);

    const char *err = ap_check_cmd_context(cmd, NOT_IN_DIR_LOC_FILE);
    if (err != NULL) {
        return err;
    }

    conf->gprof_dir = arg;
    return NULL;
}
#endif /*GPROF*/

static const char *set_add_default_charset(cmd_parms *cmd,
                                           void *d_, const char *arg)
