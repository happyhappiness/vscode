#include "h2_ctx.h"
#include "h2_conn.h"
#include "h2_h2.h"
#include "h2_switch.h"

/*******************************************************************************
 * Once per lifetime init, retrieve optional functions
 */
apr_status_t h2_switch_init(apr_pool_t *pool, server_rec *s)
{
    (void)pool;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "h2_switch init");

    return APR_SUCCESS;
}

static int h2_protocol_propose(conn_rec *c, request_rec *r,
                               server_rec *s,
                               const apr_array_header_t *offers,
                               apr_array_header_t *proposals)
{
    int proposed = 0;
    int is_tls = h2_h2_is_tls(c);
    const char **protos = is_tls? h2_tls_protos : h2_clear_protos;
    
    (void)s;
    if (strcmp(AP_PROTOCOL_HTTP1, ap_get_protocol(c))) {
        /* We do not know how to switch from anything else but http/1.1.
         */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "protocol switch: current proto != http/1.1, declined");
        return DECLINED;
    }
    
    if (!h2_is_acceptable_connection(c, 0)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c,
                      "protocol propose: connection requirements not met");
        return DECLINED;
    }
    
    if (r) {
        /* So far, this indicates an HTTP/1 Upgrade header initiated
         * protocol switch. For that, the HTTP2-Settings header needs
         * to be present and valid for the connection.
         */
        const char *p;
        
        if (!h2_allows_h2_upgrade(c)) {
            return DECLINED;
        }
         
        p = apr_table_get(r->headers_in, "HTTP2-Settings");
        if (!p) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "upgrade without HTTP2-Settings declined");
            return DECLINED;
        }
