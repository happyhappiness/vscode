/* Load balancer module for Apache proxy */

#include "mod_proxy.h"
#include "scoreboard.h"
#include "ap_mpm.h"
#include "apr_version.h"
#include "ap_hooks.h"
#include "apr_date.h"

static const char *balancer_mutex_type = "proxy-balancer-shm";
ap_slotmem_provider_t *storage = NULL;

module AP_MODULE_DECLARE_DATA proxy_balancer_module;

static int (*ap_proxy_retry_worker_fn)(const char *proxy_function,
        proxy_worker *worker, server_rec *s) = NULL;

/*
 * Register our mutex type before the config is read so we
 * can adjust the mutex settings using the Mutex directive.
 */
static int balancer_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                               apr_pool_t *ptemp)
{

    apr_status_t rv;

    rv = ap_mutex_register(pconf, balancer_mutex_type, NULL,
                               APR_LOCK_DEFAULT, 0);
    if (rv != APR_SUCCESS) {
        return rv;
    }

    return OK;
}

#if 0
extern void proxy_update_members(proxy_balancer **balancer, request_rec *r,
                                 proxy_server_conf *conf);
#endif

static int proxy_balancer_canon(request_rec *r, char *url)
{
    char *host, *path;
    char *search = NULL;
    const char *err;
    apr_port_t port = 0;

    /* TODO: offset of BALANCER_PREFIX ?? */
    if (strncasecmp(url, "balancer:", 9) == 0) {
        url += 9;
    }
    else {
        return DECLINED;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "canonicalising URL %s", url);

    /* do syntatic check.
     * We break the URL into host, port, path, search
     */
    err = ap_proxy_canon_netloc(r->pool, &url, NULL, NULL, &host, &port);
    if (err) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01157)
                      "error parsing URL %s: %s",
                      url, err);
        return HTTP_BAD_REQUEST;
    }
    /*
     * now parse path/search args, according to rfc1738:
