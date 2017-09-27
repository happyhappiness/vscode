#include "h2_config.h"
#include "h2_ctx.h"
#include "h2_from_h1.h"
#include "h2_h2.h"
#include "h2_mplx.h"
#include "h2_request.h"
#include "h2_session.h"
#include "h2_stream.h"
#include "h2_task.h"
#include "h2_worker.h"
#include "h2_util.h"

/*******************************************************************************
 * task input handling
 ******************************************************************************/

static int input_ser_header(void *ctx, const char *name, const char *value) 
{
    h2_task *task = ctx;
    apr_brigade_printf(task->input.bb, NULL, NULL, "%s: %s\r\n", name, value);
    return 1;
}

static void make_chunk(h2_task *task, apr_bucket_brigade *bb, 
                       apr_bucket *first, apr_uint64_t chunk_len, 
                       apr_bucket *tail)
{
    /* Surround the buckets [first, tail[ with new buckets carrying the
     * HTTP/1.1 chunked encoding format. If tail is NULL, the chunk extends
     * to the end of the brigade. */
    char buffer[128];
    apr_bucket *c;
    int len;
    
    len = apr_snprintf(buffer, H2_ALEN(buffer), 
                       "%"APR_UINT64_T_HEX_FMT"\r\n", chunk_len);
    c = apr_bucket_heap_create(buffer, len, NULL, bb->bucket_alloc);
    APR_BUCKET_INSERT_BEFORE(first, c);
    c = apr_bucket_heap_create("\r\n", 2, NULL, bb->bucket_alloc);
    if (tail) {
        APR_BUCKET_INSERT_BEFORE(tail, c);
    }
    else {
        APR_BRIGADE_INSERT_TAIL(bb, c);
    }
}

static apr_status_t input_handle_eos(h2_task *task, request_rec *r, 
                                     apr_bucket *b)
{
    apr_status_t status = APR_SUCCESS;
    apr_bucket_brigade *bb = task->input.bb;
    apr_table_t *t = task->request? task->request->trailers : NULL;

    if (task->input.chunked) {
        task->input.tmp = apr_brigade_split_ex(bb, b, task->input.tmp);
        if (t && !apr_is_empty_table(t)) {
            status = apr_brigade_puts(bb, NULL, NULL, "0\r\n");
            apr_table_do(input_ser_header, task, t, NULL);
            status = apr_brigade_puts(bb, NULL, NULL, "\r\n");
        }
        else {
            status = apr_brigade_puts(bb, NULL, NULL, "0\r\n\r\n");
        }
        APR_BRIGADE_CONCAT(bb, task->input.tmp);
    }
    else if (r && t && !apr_is_empty_table(t)){
        /* trailers passed in directly. */
        apr_table_overlap(r->trailers_in, t, APR_OVERLAP_TABLES_SET);
    }
    task->input.eos_written = 1;
    return status;
}

static apr_status_t input_append_eos(h2_task *task, request_rec *r)
{
    apr_status_t status = APR_SUCCESS;
    apr_bucket_brigade *bb = task->input.bb;
    apr_table_t *t = task->request? task->request->trailers : NULL;

    if (task->input.chunked) {
        if (t && !apr_is_empty_table(t)) {
            status = apr_brigade_puts(bb, NULL, NULL, "0\r\n");
            apr_table_do(input_ser_header, task, t, NULL);
            status = apr_brigade_puts(bb, NULL, NULL, "\r\n");
        }
        else {
            status = apr_brigade_puts(bb, NULL, NULL, "0\r\n\r\n");
        }
    }
    else if (r && t && !apr_is_empty_table(t)){
        /* trailers passed in directly. */
        apr_table_overlap(r->trailers_in, t, APR_OVERLAP_TABLES_SET);
    }
    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_eos_create(bb->bucket_alloc));
    task->input.eos_written = 1;
    return status;
}

static apr_status_t input_read(h2_task *task, ap_filter_t* f,
                               apr_bucket_brigade* bb, ap_input_mode_t mode,
                               apr_read_type_e block, apr_off_t readbytes)
{
    apr_status_t status = APR_SUCCESS;
    apr_bucket *b, *next, *first_data;
    apr_off_t bblen = 0;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                  "h2_task(%s): read, mode=%d, block=%d, readbytes=%ld", 
                  task->id, mode, block, (long)readbytes);
    
    if (mode == AP_MODE_INIT) {
        return ap_get_brigade(f->c->input_filters, bb, mode, block, readbytes);
    }
    
    if (f->c->aborted || !task->request) {
        return APR_ECONNABORTED;
    }
    
    if (!task->input.bb) {
        if (!task->input.eos_written) {
            input_append_eos(task, f->r);
            return APR_SUCCESS;
        }
        return APR_EOF;
    }
    
    /* Cleanup brigades from those nasty 0 length non-meta buckets
     * that apr_brigade_split_line() sometimes produces. */
    for (b = APR_BRIGADE_FIRST(task->input.bb);
