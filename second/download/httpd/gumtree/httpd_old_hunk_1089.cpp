
    *url = apr_pstrcat(r->pool, worker->name, path, NULL);

    return OK;
}

static int proxy_balancer_pre_request(proxy_worker **worker,
                                      proxy_balancer **balancer,
                                      request_rec *r,
                                      proxy_server_conf *conf, char **url)
{
    int access_status;
