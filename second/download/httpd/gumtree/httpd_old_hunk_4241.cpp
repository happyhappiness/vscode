#include "h2_private.h"
#include "h2_push.h"
#include "h2_request.h"
#include "h2_util.h"


h2_request *h2_request_create(int id, apr_pool_t *pool, int serialize)
{
    return h2_request_createn(id, pool, NULL, NULL, NULL, NULL, NULL,
                              serialize);
}

h2_request *h2_request_createn(int id, apr_pool_t *pool,
                               const char *method, const char *scheme,
                               const char *authority, const char *path,
                               apr_table_t *header, int serialize)
{
    h2_request *req = apr_pcalloc(pool, sizeof(h2_request));
    
    req->id             = id;
    req->method         = method;
    req->scheme         = scheme;
    req->authority      = authority;
    req->path           = path;
    req->headers        = header? header : apr_table_make(pool, 10);
    req->request_time   = apr_time_now();
    req->serialize      = serialize;
    
    return req;
}

static apr_status_t inspect_clen(h2_request *req, const char *s)
{
    char *end;
    req->content_length = apr_strtoi64(s, &end, 10);
    return (s == end)? APR_EINVAL : APR_SUCCESS;
}

static apr_status_t add_h1_header(h2_request *req, apr_pool_t *pool, 
                                  const char *name, size_t nlen,
                                  const char *value, size_t vlen)
{
    char *hname, *hvalue;
    
    if (h2_req_ignore_header(name, nlen)) {
        return APR_SUCCESS;
    }
    else if (H2_HD_MATCH_LIT("cookie", name, nlen)) {
        const char *existing = apr_table_get(req->headers, "cookie");
        if (existing) {
            char *nval;
            
            /* Cookie header come separately in HTTP/2, but need
             * to be merged by "; " (instead of default ", ")
             */
            hvalue = apr_pstrndup(pool, value, vlen);
            nval = apr_psprintf(pool, "%s; %s", existing, hvalue);
            apr_table_setn(req->headers, "Cookie", nval);
            return APR_SUCCESS;
        }
    }
    else if (H2_HD_MATCH_LIT("host", name, nlen)) {
        if (apr_table_get(req->headers, "Host")) {
            return APR_SUCCESS; /* ignore duplicate */
        }
    }
    
    hname = apr_pstrndup(pool, name, nlen);
    hvalue = apr_pstrndup(pool, value, vlen);
    h2_util_camel_case_header(hname, nlen);
    apr_table_mergen(req->headers, hname, hvalue);
    
    return APR_SUCCESS;
}

typedef struct {
    h2_request *req;
    apr_pool_t *pool;
} h1_ctx;

static int set_h1_header(void *ctx, const char *key, const char *value)
{
    h1_ctx *x = ctx;
    size_t klen = strlen(key);
    if (!h2_req_ignore_header(key, klen)) {
        add_h1_header(x->req, x->pool, key, klen, value, strlen(value));
    }
    return 1;
}

static apr_status_t add_all_h1_header(h2_request *req, apr_pool_t *pool, 
                                      apr_table_t *header)
{
    h1_ctx x;
    x.req = req;
    x.pool = pool;
    apr_table_do(set_h1_header, &x, header, NULL);
    return APR_SUCCESS;
}


apr_status_t h2_request_make(h2_request *req, apr_pool_t *pool,
                             const char *method, const char *scheme, 
                             const char *authority, const char *path, 
                             apr_table_t *headers)
{
    req->method    = method;
    req->scheme    = scheme;
    req->authority = authority;
    req->path      = path;

    AP_DEBUG_ASSERT(req->scheme);
    AP_DEBUG_ASSERT(req->authority);
    AP_DEBUG_ASSERT(req->path);
    AP_DEBUG_ASSERT(req->method);

    return add_all_h1_header(req, pool, headers);
}

apr_status_t h2_request_rwrite(h2_request *req, request_rec *r)
{
    apr_status_t status;
    const char *scheme, *authority;
    
    scheme = (r->parsed_uri.scheme? r->parsed_uri.scheme
              : ap_http_scheme(r));
    authority = r->hostname;
    if (!ap_strchr_c(authority, ':') && r->server && r->server->port) {
        apr_port_t defport = apr_uri_port_of_scheme(scheme);
        if (defport != r->server->port) {
            /* port info missing and port is not default for scheme: append */
            authority = apr_psprintf(r->pool, "%s:%d", authority,
                                     (int)r->server->port);
        }
    }
    
    status = h2_request_make(req, r->pool,  r->method, scheme, authority,
                             apr_uri_unparse(r->pool, &r->parsed_uri, 
                                             APR_URI_UNP_OMITSITEPART),
                             r->headers_in);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(03058)
                  "h2_request(%d): rwrite %s host=%s://%s%s",
                  req->id, req->method, req->scheme, req->authority, req->path);
    return status;
}

apr_status_t h2_request_add_header(h2_request *req, apr_pool_t *pool, 
                                   const char *name, size_t nlen,
                                   const char *value, size_t vlen)
