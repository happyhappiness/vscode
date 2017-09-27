
#include "h2_filter.h"

#define UNSET       -1
#define H2MIN(x,y) ((x) < (y) ? (x) : (y))

static apr_status_t recv_RAW_DATA(conn_rec *c, h2_filter_cin *cin, 
                                  apr_bucket *b, apr_read_type_e block)
{
    h2_session *session = cin->session;
    apr_status_t status = APR_SUCCESS;
    apr_size_t len;
    const char *data;
    ssize_t n;
    
    status = apr_bucket_read(b, &data, &len, block);
    
    while (status == APR_SUCCESS && len > 0) {
        n = nghttp2_session_mem_recv(session->ngh2, (const uint8_t *)data, len);
        
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, session->c,
                      H2_SSSN_MSG(session, "fed %ld bytes to nghttp2, %ld read"),
                      (long)len, (long)n);
        if (n < 0) {
            if (nghttp2_is_fatal((int)n)) {
                h2_session_event(session, H2_SESSION_EV_PROTO_ERROR, 
                                 (int)n, nghttp2_strerror((int)n));
                status = APR_EGENERAL;
            }
        }
        else {
            session->io.bytes_read += n;
            if (len <= n) {
                break;
            }
            len -= n;
            data += n;
        }
    }
    
    return status;
}

static apr_status_t recv_RAW_brigade(conn_rec *c, h2_filter_cin *cin, 
                                     apr_bucket_brigade *bb, 
                                     apr_read_type_e block)
{
    apr_status_t status = APR_SUCCESS;
    apr_bucket* b;
    int consumed = 0;
    
    h2_util_bb_log(c, c->id, APLOG_TRACE2, "RAW_in", bb);
    while (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(bb)) {
        b = APR_BRIGADE_FIRST(bb);

        if (APR_BUCKET_IS_METADATA(b)) {
            /* nop */
        }
        else {
            status = recv_RAW_DATA(c, cin, b, block);
        }
        consumed = 1;
        apr_bucket_delete(b);
    }
    
    if (!consumed && status == APR_SUCCESS && block == APR_NONBLOCK_READ) {
        return APR_EAGAIN;
    }
    return status;
}

h2_filter_cin *h2_filter_cin_create(h2_session *session)
{
    h2_filter_cin *cin;
    
    cin = apr_pcalloc(session->pool, sizeof(*cin));
    if (!cin) {
        return NULL;
    }
    cin->session = session;
    return cin;
}

void h2_filter_cin_timeout_set(h2_filter_cin *cin, apr_interval_time_t timeout)
{
    cin->timeout = timeout;
