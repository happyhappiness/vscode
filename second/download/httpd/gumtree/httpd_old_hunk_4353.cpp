 * limitations under the License.
 */

#include <assert.h>
#include <stdio.h>

#include <apr_lib.h>
#include <apr_strings.h>

#include <httpd.h>
#include <http_core.h>
#include <http_log.h>
#include <http_connection.h>
#include <http_protocol.h>
#include <http_request.h>
#include <util_time.h>

#include "h2_private.h"
#include "h2_response.h"
#include "h2_from_h1.h"
#include "h2_task.h"
#include "h2_util.h"


static void set_state(h2_from_h1 *from_h1, h2_from_h1_state_t state);

h2_from_h1 *h2_from_h1_create(int stream_id, apr_pool_t *pool)
{
    h2_from_h1 *from_h1 = apr_pcalloc(pool, sizeof(h2_from_h1));
    if (from_h1) {
        from_h1->stream_id = stream_id;
        from_h1->pool = pool;
        from_h1->state = H2_RESP_ST_STATUS_LINE;
        from_h1->hlines = apr_array_make(pool, 10, sizeof(char *));
    }
    return from_h1;
}

static void set_state(h2_from_h1 *from_h1, h2_from_h1_state_t state)
{
    if (from_h1->state != state) {
        from_h1->state = state;
    }
}

h2_response *h2_from_h1_get_response(h2_from_h1 *from_h1)
{
    return from_h1->response;
}

static apr_status_t make_h2_headers(h2_from_h1 *from_h1, request_rec *r)
{
    from_h1->response = h2_response_create(from_h1->stream_id, 0,
                                           from_h1->http_status, 
                                           from_h1->hlines,
                                           r->notes,
                                           from_h1->pool);
    from_h1->content_length = from_h1->response->content_length;
    from_h1->chunked = r->chunked;
    
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, r->connection, APLOGNO(03197)
                  "h2_from_h1(%d): converted headers, content-length: %d"
                  ", chunked=%d",
                  from_h1->stream_id, (int)from_h1->content_length, 
                  (int)from_h1->chunked);
    
    set_state(from_h1, ((from_h1->chunked || from_h1->content_length > 0)?
                        H2_RESP_ST_BODY : H2_RESP_ST_DONE));
    /* We are ready to be sent to the client */
    return APR_SUCCESS;
}

static apr_status_t parse_header(h2_from_h1 *from_h1, ap_filter_t* f, 
                                 char *line) {
    (void)f;
    
    if (line[0] == ' ' || line[0] == '\t') {
        char **plast;
        /* continuation line from the header before this */
        while (line[0] == ' ' || line[0] == '\t') {
            ++line;
        }
        
        plast = apr_array_pop(from_h1->hlines);
        if (plast == NULL) {
            /* not well formed */
            return APR_EINVAL;
        }
        APR_ARRAY_PUSH(from_h1->hlines, const char*) = apr_psprintf(from_h1->pool, "%s %s", *plast, line);
    }
    else {
        /* new header line */
        APR_ARRAY_PUSH(from_h1->hlines, const char*) = apr_pstrdup(from_h1->pool, line);
    }
    return APR_SUCCESS;
}

static apr_status_t get_line(h2_from_h1 *from_h1, apr_bucket_brigade *bb,
                             ap_filter_t* f, char *line, apr_size_t len)
{
    apr_status_t status;
    if (!from_h1->bb) {
        from_h1->bb = apr_brigade_create(from_h1->pool, f->c->bucket_alloc);
    }
    else {
        apr_brigade_cleanup(from_h1->bb);                
    }
    status = apr_brigade_split_line(from_h1->bb, bb, 
                                                 APR_BLOCK_READ, 
                                                 HUGE_STRING_LEN);
    if (status == APR_SUCCESS) {
        --len;
        status = apr_brigade_flatten(from_h1->bb, line, &len);
        if (status == APR_SUCCESS) {
            /* we assume a non-0 containing line and remove
             * trailing crlf. */
            line[len] = '\0';
            if (len >= 2 && !strcmp(H2_CRLF, line + len - 2)) {
                len -= 2;
                line[len] = '\0';
            }
            
            apr_brigade_cleanup(from_h1->bb);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                          "h2_from_h1(%d): read line: %s",
                          from_h1->stream_id, line);
        }
    }
    return status;
}

apr_status_t h2_from_h1_read_response(h2_from_h1 *from_h1, ap_filter_t* f,
                                      apr_bucket_brigade* bb)
{
    apr_status_t status = APR_SUCCESS;
    char line[HUGE_STRING_LEN];
    
    if ((from_h1->state == H2_RESP_ST_BODY) 
        || (from_h1->state == H2_RESP_ST_DONE)) {
        if (from_h1->chunked) {
            /* The httpd core HTTP_HEADER filter has or will install the 
             * "CHUNK" output transcode filter, which appears further down 
             * the filter chain. We do not want it for HTTP/2.
             * Once we successfully deinstalled it, this filter has no
             * further function and we remove it.
             */
            status = ap_remove_output_filter_byhandle(f->r->output_filters, 
                                                      "CHUNK");
            if (status == APR_SUCCESS) {
                ap_remove_output_filter(f);
            }
        }
        
        return ap_pass_brigade(f->next, bb);
    }
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                  "h2_from_h1(%d): read_response", from_h1->stream_id);
    
    while (!APR_BRIGADE_EMPTY(bb) && status == APR_SUCCESS) {
        
        switch (from_h1->state) {
                
            case H2_RESP_ST_STATUS_LINE:
            case H2_RESP_ST_HEADERS:
                status = get_line(from_h1, bb, f, line, sizeof(line));
                if (status != APR_SUCCESS) {
                    return status;
                }
                if (from_h1->state == H2_RESP_ST_STATUS_LINE) {
                    /* instead of parsing, just take it directly */
                    from_h1->http_status = f->r->status;
                    from_h1->state = H2_RESP_ST_HEADERS;
                }
                else if (line[0] == '\0') {
                    /* end of headers, create the h2_response and
                     * pass the rest of the brigade down the filter
                     * chain.
                     */
                    status = make_h2_headers(from_h1, f->r);
                    if (from_h1->bb) {
                        apr_brigade_destroy(from_h1->bb);
                        from_h1->bb = NULL;
                    }
                    if (!APR_BRIGADE_EMPTY(bb)) {
                        return ap_pass_brigade(f->next, bb);
                    }
                }
                else {
                    status = parse_header(from_h1, f, line);
                }
                break;
                
            default:
                return ap_pass_brigade(f->next, bb);
        }
        
    }
    
    return status;
}

/* This routine is called by apr_table_do and merges all instances of
 * the passed field values into a single array that will be further
 * processed by some later routine.  Originally intended to help split
 * and recombine multiple Vary fields, though it is generic to any field
 * consisting of comma/space-separated tokens.
 */
