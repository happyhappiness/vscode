            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                         "RewriteOptions: MaxRedirects option has been "
                         "removed in favor of the global "
                         "LimitInternalRecursion directive and will be "
                         "ignored.");
        }
        else {
            return apr_pstrcat(cmd->pool, "RewriteOptions: unknown option '",
                               w, "'", NULL);
        }
    }

    /* put it into the appropriate config */
    if (cmd->path == NULL) { /* is server command */
        rewrite_server_conf *conf =
            ap_get_module_config(cmd->server->module_config,
                                 &rewrite_module);

        conf->options |= options;
    }
    else {                  /* is per-directory command */
        rewrite_perdir_conf *conf = in_dconf;

        conf->options |= options;
    }

    return NULL;
}

static const char *cmd_rewritemap(cmd_parms *cmd, void *dconf, const char *a1,
                                  const char *a2)
{
    rewrite_server_conf *sconf;
    rewritemap_entry *newmap;
    apr_finfo_t st;
