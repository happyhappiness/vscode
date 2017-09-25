                apr_pool_cleanup_register(pconf, lr, nwssl_socket_cleanup, apr_pool_cleanup_null);
            }
        } else {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    } 

    for (slu = ap_seclistenersup; slu; slu = slu->next) {
        /* Check the listener list for a matching upgradeable listener */
        found = 0;
        for (lr = ap_listeners; lr; lr = lr->next) {
            if (slu->port == lr->bind_addr->port) {
                found = 1;
                break;
            }
        }
        if (!found) {
            ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, plog,
                         "No Listen directive found for upgradeable listener %s:%d", slu->addr, slu->port);
        }
    }    

    build_cert_list(pconf);

    return OK;
}

static void *nwssl_config_server_create(apr_pool_t *p, server_rec *s)
{
    NWSSLSrvConfigRec *new = apr_palloc(p, sizeof(NWSSLSrvConfigRec));
    new->sltable = apr_table_make(p, 5);
    new->slutable = apr_table_make(p, 5);
    return new;
}

static void *nwssl_config_server_merge(apr_pool_t *p, void *basev, void *addv)
{
    NWSSLSrvConfigRec *base = (NWSSLSrvConfigRec *)basev;
    NWSSLSrvConfigRec *add  = (NWSSLSrvConfigRec *)addv;
    NWSSLSrvConfigRec *merged  = (NWSSLSrvConfigRec *)apr_palloc(p, sizeof(NWSSLSrvConfigRec));
    return merged;
}

static int compare_ipports(void *rec, const char *key, const char *value)
{
    conn_rec *c = (conn_rec*)rec;

    if (value && 
        ((strcmp(value, "0.0.0.0") == 0) || (strcmp(value, c->local_ip) == 0))) 
    {
        return 0;
    }
    return 1;
}

static int isSecureConnEx (const server_rec *s, const conn_rec *c, const apr_table_t *t)
{
    char port[8];

    itoa((c->local_addr)->port, port, 10);
    if (!apr_table_do(compare_ipports, (void*)c, t, port, NULL))
    {
        return 1;
    }

    return 0;
}

static int isSecureConn (const server_rec *s, const conn_rec *c)
{
    NWSSLSrvConfigRec *sc = get_nwssl_cfg(s);

    return isSecureConnEx (s, c, sc->sltable);
}

static int isSecureConnUpgradeable (const server_rec *s, const conn_rec *c)
{
    NWSSLSrvConfigRec *sc = get_nwssl_cfg(s);

    return isSecureConnEx (s, c, sc->slutable);
}

static int isSecure (const request_rec *r)
{
	return isSecureConn (r->server, r->connection);
}

static int isSecureUpgradeable (const request_rec *r)
{
	return isSecureConnUpgradeable (r->server, r->connection);
}

static int nwssl_hook_Fixup(request_rec *r)
{
    int i;

    if (!isSecure(r))
        return DECLINED;
