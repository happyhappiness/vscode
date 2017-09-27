#include "h2_private.h"
#include "h2_push.h"
#include "h2_request.h"
#include "h2_util.h"


static apr_status_t inspect_clen(h2_request *req, const char *s)
{
    char *end;
    req->content_length = apr_strtoi64(s, &end, 10);
    return (s == end)? APR_EINVAL : APR_SUCCESS;
}

apr_status_t h2_request_rwrite(h2_request *req, apr_pool_t *pool, 
                               request_rec *r)
{
    apr_status_t status;
    const char *scheme, *authority;
    
    scheme = apr_pstrdup(pool, r->parsed_uri.scheme? r->parsed_uri.scheme
              : ap_http_scheme(r));
    authority = apr_pstrdup(pool, r->hostname);
    if (!ap_strchr_c(authority, ':') && r->server && r->server->port) {
        apr_port_t defport = apr_uri_port_of_scheme(scheme);
        if (defport != r->server->port) {
            /* port info missing and port is not default for scheme: append */
            authority = apr_psprintf(pool, "%s:%d", authority,
                                     (int)r->server->port);
        }
    }
    
    status = h2_req_make(req, pool, apr_pstrdup(pool, r->method), scheme, 
                         authority, apr_uri_unparse(pool, &r->parsed_uri, 
                                                    APR_URI_UNP_OMITSITEPART),
                         r->headers_in);
    return status;
}

apr_status_t h2_request_add_header(h2_request *req, apr_pool_t *pool, 
                                   const char *name, size_t nlen,
                                   const char *value, size_t vlen)
