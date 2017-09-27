    }
    else {
        return 0;
    }
}

static int find_allowdeny(request_rec *r, apr_array_header_t *a, int method)
{

    allowdeny *ap = (allowdeny *) a->elts;
    apr_int64_t mmask = (AP_METHOD_BIT << method);
    int i;
    int gothost = 0;
    const char *remotehost = NULL;

    for (i = 0; i < a->nelts; ++i) {
        if (!(mmask & ap[i].limited)) {
            continue;
        }

        switch (ap[i].type) {
        case T_ENV:
            if (apr_table_get(r->subprocess_env, ap[i].x.from)) {
                return 1;
            }
            break;

        case T_NENV:
            if (!apr_table_get(r->subprocess_env, ap[i].x.from)) {
                return 1;
            }
            break;

        case T_ALL:
            return 1;

        case T_IP:
            if (apr_ipsubnet_test(ap[i].x.ip, r->connection->remote_addr)) {
                return 1;
            }
            break;

        case T_HOST:
            if (!gothost) {
                int remotehost_is_ip;

                remotehost = ap_get_remote_host(r->connection,
                                                r->per_dir_config,
                                                REMOTE_DOUBLE_REV,
                                                &remotehost_is_ip);

                if ((remotehost == NULL) || remotehost_is_ip) {
                    gothost = 1;
                }
                else {
                    gothost = 2;
                }
            }

            if ((gothost == 2) && in_domain(ap[i].x.from, remotehost)) {
                return 1;
            }
            break;

        case T_FAIL:
            /* do nothing? */
            break;
        }
    }

    return 0;
}

static int check_dir_access(request_rec *r)
{
    int method = r->method_number;
    int ret = OK;
    authz_host_dir_conf *a = (authz_host_dir_conf *)
        ap_get_module_config(r->per_dir_config, &authz_host_module);

    if (a->order[method] == ALLOW_THEN_DENY) {
        ret = HTTP_FORBIDDEN;
        if (find_allowdeny(r, a->allows, method)) {
            ret = OK;
        }
        if (find_allowdeny(r, a->denys, method)) {
            ret = HTTP_FORBIDDEN;
        }
    }
    else if (a->order[method] == DENY_THEN_ALLOW) {
        if (find_allowdeny(r, a->denys, method)) {
            ret = HTTP_FORBIDDEN;
        }
        if (find_allowdeny(r, a->allows, method)) {
            ret = OK;
        }
    }
    else {
        if (find_allowdeny(r, a->allows, method)
            && !find_allowdeny(r, a->denys, method)) {
            ret = OK;
        }
        else {
            ret = HTTP_FORBIDDEN;
        }
    }

    if (ret == HTTP_FORBIDDEN
        && (ap_satisfies(r) != SATISFY_ANY || !ap_some_auth_required(r))) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
            "client denied by server configuration: %s%s",
            r->filename ? "" : "uri ",
            r->filename ? r->filename : r->uri);
    }

    return ret;
}

static void register_hooks(apr_pool_t *p)
{
    /* This can be access checker since we don't require r->user to be set. */
    ap_hook_access_checker(check_dir_access,NULL,NULL,APR_HOOK_MIDDLE);
}

module AP_MODULE_DECLARE_DATA authz_host_module =
{
    STANDARD20_MODULE_STUFF,
    create_authz_host_dir_config,   /* dir config creater */
    NULL,                           /* dir merger --- default is to override */
    NULL,                           /* server config */
    NULL,                           /* merge server config */
