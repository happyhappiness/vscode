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
                                                 ml->m,
                                                 parms->pool);
        const char *retval;
        cmd = ml->cmd;

        /* Once was enough? */
        if (cmd->req_override & EXEC_ON_READ) {
            continue;
        }

        retval = invoke_cmd(cmd, parms, dir_config, current->args);

        if (retval != NULL && strcmp(retval, DECLINE_CMD) != 0) {
            /* If the directive in error has already been set, don't
             * replace it.  Otherwise, an error inside a container
             * will be reported as occuring on the first line of the
             * container.
             */
            if (!parms->err_directive) {
                parms->err_directive = current;
            }
            return retval;
        }
    }

    return NULL;
}