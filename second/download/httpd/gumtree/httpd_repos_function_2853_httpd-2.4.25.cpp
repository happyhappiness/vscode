static const char *h2_conf_add_push_res(cmd_parms *cmd, void *dirconf,
                                        const char *arg1, const char *arg2,
                                        const char *arg3)
{
    h2_config *dconf = (h2_config*)dirconf ;
    h2_config *sconf = (h2_config*)h2_config_sget(cmd->server);
    h2_push_res push;
    const char *last = arg3;
    
    memset(&push, 0, sizeof(push));
    if (!strcasecmp("add", arg1)) {
        push.uri_ref = arg2;
    }
    else {
        push.uri_ref = arg1;
        last = arg2;
        if (arg3) {
            return "too many parameter";
        }
    }
    
    if (last) {
        if (!strcasecmp("critical", last)) {
            push.critical = 1;
        }
        else {
            return "unknown last parameter";
        }
    }

    /* server command? set both */
    if (cmd->path == NULL) {
        add_push(cmd->pool, sconf, &push);
        add_push(cmd->pool, dconf, &push);
    }
    else {
        add_push(cmd->pool, dconf, &push);
    }

    return NULL;
}