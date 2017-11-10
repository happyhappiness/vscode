static const char *set_qop(cmd_parms *cmd, void *config, const char *op)
{
    digest_config_rec *conf = (digest_config_rec *) config;
    char **tmp;
    int cnt;

    if (!strcasecmp(op, "none")) {
        if (conf->qop_list[0] == NULL) {
            conf->qop_list = apr_palloc(cmd->pool, 2 * sizeof(char*));
            conf->qop_list[1] = NULL;
        }
        conf->qop_list[0] = "none";
        return NULL;
    }

    if (!strcasecmp(op, "auth-int")) {
        return "AuthDigestQop auth-int is not implemented";
    }
    else if (strcasecmp(op, "auth")) {
        return apr_pstrcat(cmd->pool, "Unrecognized qop: ", op, NULL);
    }

    for (cnt = 0; conf->qop_list[cnt] != NULL; cnt++)
        ;

    tmp = apr_palloc(cmd->pool, (cnt + 2) * sizeof(char*));
    memcpy(tmp, conf->qop_list, cnt*sizeof(char*));
    tmp[cnt]   = apr_pstrdup(cmd->pool, op);
    tmp[cnt+1] = NULL;
    conf->qop_list = tmp;

    return NULL;
}