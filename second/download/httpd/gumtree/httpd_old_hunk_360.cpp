                apr_pool_cleanup_register(pconf, lr, nwssl_socket_cleanup, apr_pool_cleanup_null);
            }
        } else {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    } 
    build_cert_list(pconf);

    return OK;
}

static void *nwssl_config_server_create(apr_pool_t *p, server_rec *s)
{
    NWSSLSrvConfigRec *new = apr_palloc(p, sizeof(NWSSLSrvConfigRec));
    new->sltable = apr_table_make(p, 5);
    return new;
}

static void *nwssl_config_server_merge(apr_pool_t *p, void *basev, void *addv)
{
    NWSSLSrvConfigRec *base = (NWSSLSrvConfigRec *)basev;
    NWSSLSrvConfigRec *add  = (NWSSLSrvConfigRec *)addv;
    NWSSLSrvConfigRec *merged  = (NWSSLSrvConfigRec *)apr_palloc(p, sizeof(NWSSLSrvConfigRec));
    return merged;
}

static int isSecureConn (const server_rec *s, const conn_rec *c)
{
    NWSSLSrvConfigRec *sc = get_nwssl_cfg(s);
    const char *s_secure = NULL;
    char port[8];
    int ret = 0;

    itoa((c->local_addr)->port, port, 10);
    s_secure = apr_table_get(sc->sltable, port);    
    if (s_secure)
        ret = 1;

    return ret;
}

static int isSecure (const request_rec *r)
{
	return isSecureConn (r->server, r->connection);
}

static int nwssl_hook_Fixup(request_rec *r)
{
    int i;

    if (!isSecure(r))
        return DECLINED;
