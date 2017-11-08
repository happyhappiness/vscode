static const char *ap_build_config_sub(apr_pool_t *p, apr_pool_t *temp_pool,
                                       const char *l, cmd_parms *parms,
                                       ap_directive_t **current,
                                       ap_directive_t **curr_parent,
                                       ap_directive_t **conftree)
{
    const char *retval = NULL;
    const char *args;
    char *cmd_name;
    ap_directive_t *newdir;
    module *mod = ap_top_module;
    const command_rec *cmd;

    if (*l == '#' || *l == '\0')
        return NULL;

#if RESOLVE_ENV_PER_TOKEN
    args = l;
#else
    args = ap_resolve_env(temp_pool, l);
#endif

    cmd_name = ap_getword_conf(p, &args);
    if (*cmd_name == '\0') {
        /* Note: this branch should not occur. An empty line should have
         * triggered the exit further above.
         */
        return NULL;
    }

    if (cmd_name[1] != '/') {
        char *lastc = cmd_name + strlen(cmd_name) - 1;
        if (*lastc == '>') {
            *lastc = '\0' ;
        }
        if (cmd_name[0] == '<' && *args == '\0') {
            args = ">";
        }
    }

    newdir = apr_pcalloc(p, sizeof(ap_directive_t));
    newdir->filename = parms->config_file->name;
    newdir->line_num = parms->config_file->line_number;
    newdir->directive = cmd_name;
    newdir->args = apr_pstrdup(p, args);

    if ((cmd = ap_find_command_in_modules(cmd_name, &mod)) != NULL) {
        if (cmd->req_override & EXEC_ON_READ) {
            ap_directive_t *sub_tree = NULL;

            parms->err_directive = newdir;
            retval = execute_now(cmd_name, args, parms, p, temp_pool,
                                 &sub_tree, *curr_parent);
            if (*current) {
                (*current)->next = sub_tree;
            }
            else {
                *current = sub_tree;
                if (*curr_parent) {
                    (*curr_parent)->first_child = (*current);
                }
                if (*current) {
                    (*current)->parent = (*curr_parent);
                }
            }
            if (*current) {
                if (!*conftree) {
                    /* Before walking *current to the end of the list,
                     * set the head to *current.
                     */
                    *conftree = *current;
                }
                while ((*current)->next != NULL) {
                    (*current) = (*current)->next;
                    (*current)->parent = (*curr_parent);
                }
            }
            return retval;
        }
    }

    if (cmd_name[0] == '<') {
        if (cmd_name[1] != '/') {
            (*current) = ap_add_node(curr_parent, *current, newdir, 1);
        }
        else if (*curr_parent == NULL) {
            parms->err_directive = newdir;
            return apr_pstrcat(p, cmd_name,
                               " without matching <", cmd_name + 2,
                               " section", NULL);
        }
        else {
            char *bracket = cmd_name + strlen(cmd_name) - 1;

            if (*bracket != '>') {
                parms->err_directive = newdir;
                return apr_pstrcat(p, cmd_name,
                                   "> directive missing closing '>'", NULL);
            }

            *bracket = '\0';

            if (strcasecmp(cmd_name + 2,
                           (*curr_parent)->directive + 1) != 0) {
                parms->err_directive = newdir;
                return apr_pstrcat(p, "Expected </",
                                   (*curr_parent)->directive + 1, "> but saw ",
                                   cmd_name, ">", NULL);
            }

            *bracket = '>';

            /* done with this section; move up a level */
            *current = *curr_parent;
            *curr_parent = (*current)->parent;
        }
    }
    else {
        *current = ap_add_node(curr_parent, *current, newdir, 0);
    }

    return retval;
}