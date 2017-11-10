static const char *ap_walk_config_sub(const ap_directive_t *current,
                                      cmd_parms *parms,
                                      ap_conf_vector_t *section_vector)
{
    module *mod = ap_top_module;

    while (1) {
        const command_rec *cmd;

        if (!(cmd = ap_find_command_in_modules(current->directive, &mod))) {
            parms->err_directive = current;
            return apr_pstrcat(parms->pool, "Invalid command '",
                               current->directive,
                               "', perhaps mis-spelled or defined by a module "
                               "not included in the server configuration",
                               NULL);
        }
        else {
            void *dir_config = ap_set_config_vectors(parms->server,
                                                     section_vector,
                                                     parms->path,
                                                     mod,
                                                     parms->pool);
            const char *retval;

            /* Once was enough? */
            if (cmd->req_override & EXEC_ON_READ) {
                return NULL;
            }

            retval = invoke_cmd(cmd, parms, dir_config, current->args);
            if (retval == NULL) {
                return NULL;
            }

            if (strcmp(retval, DECLINE_CMD) != 0) {
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

            mod = mod->next; /* Next time around, skip this one */
        }
    }
    /* NOTREACHED */
}