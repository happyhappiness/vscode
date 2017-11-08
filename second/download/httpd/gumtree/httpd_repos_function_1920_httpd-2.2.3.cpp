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