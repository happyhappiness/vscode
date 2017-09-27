#include "h2_config.h"
#include "h2_ctx.h"
#include "h2_from_h1.h"
#include "h2_h2.h"
#include "h2_mplx.h"
#include "h2_request.h"
#include "h2_headers.h"
#include "h2_session.h"
#include "h2_stream.h"
#include "h2_task.h"
#include "h2_worker.h"
#include "h2_util.h"

static void H2_TASK_OUT_LOG(int lvl, h2_task *task, apr_bucket_brigade *bb, 
                            const char *tag)
{
    if (APLOG_C_IS_LEVEL(task->c, lvl)) {
        conn_rec *c = task->c;
        char buffer[4 * 1024];
        const char *line = "(null)";
        apr_size_t len, bmax = sizeof(buffer)/sizeof(buffer[0]);
        
        len = h2_util_bb_print(buffer, bmax, tag, "", bb);
        ap_log_cerror(APLOG_MARK, lvl, 0, c, "bb_dump(%s): %s", 
                      task->id, len? buffer : line);
    }
}

/*******************************************************************************
 * task input handling
 ******************************************************************************/

static int input_ser_header(void *ctx, const char *name, const char *value) 
{
    h2_task *task = ctx;
    apr_brigade_printf(task->input.bb, NULL, NULL, "%s: %s\r\n", name, value);
    return 1;
}

/*******************************************************************************
 * task output handling
 ******************************************************************************/

static apr_status_t open_output(h2_task *task)
{
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, APLOGNO(03348)
                  "h2_task(%s): open output to %s %s %s",
                  task->id, task->request->method, 
                  task->request->authority, 
                  task->request->path);
    task->output.opened = 1;
    return h2_mplx_out_open(task->mplx, task->stream_id, task->output.beam);
}

static apr_status_t send_out(h2_task *task, apr_bucket_brigade* bb, int block)
{
    apr_off_t written, left;
    apr_status_t status;

    apr_brigade_length(bb, 0, &written);
    H2_TASK_OUT_LOG(APLOG_TRACE2, task, bb, "h2_task send_out");
    /* engines send unblocking */
    status = h2_beam_send(task->output.beam, bb, 
                          block? APR_BLOCK_READ : APR_NONBLOCK_READ);
    if (APR_STATUS_IS_EAGAIN(status)) {
        apr_brigade_length(bb, 0, &left);
        written -= left;
        status = APR_SUCCESS;
    }
    if (status == APR_SUCCESS) {
        if (h2_task_logio_add_bytes_out) {
            h2_task_logio_add_bytes_out(task->c, written);
        }
        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, task->c, 
                      "h2_task(%s): send_out done", task->id);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, task->c,
                      "h2_task(%s): send_out (%ld bytes)", 
                      task->id, (long)written);
    }
    return status;
}

/* Bring the data from the brigade (which represents the result of the
 * request_rec out filter chain) into the h2_mplx for further sending
 * on the master connection. 
 */
static apr_status_t slave_out(h2_task *task, ap_filter_t* f, 
                              apr_bucket_brigade* bb)
{
    apr_bucket *b;
    apr_status_t status = APR_SUCCESS;
    int flush = 0, blocking;
    
    if (task->frozen) {
        h2_util_bb_log(task->c, task->stream_id, APLOG_TRACE2,
                       "frozen task output write, ignored", bb);
        while (!APR_BRIGADE_EMPTY(bb)) {
            b = APR_BRIGADE_FIRST(bb);
            if (AP_BUCKET_IS_EOR(b)) {
                APR_BUCKET_REMOVE(b);
                task->eor = b;
            }
            else {
                apr_bucket_delete(b);
            }
        }
        return APR_SUCCESS;
    }

    /* we send block once we opened the output, so someone is there
     * reading it *and* the task is not assigned to a h2_req_engine */
    blocking = (!task->assigned && task->output.opened);
    if (!task->output.opened) {
        for (b = APR_BRIGADE_FIRST(bb);
             b != APR_BRIGADE_SENTINEL(bb);
             b = APR_BUCKET_NEXT(b)) {
            if (APR_BUCKET_IS_FLUSH(b)) {
                flush = 1;
                break;
            }
        }
    }
    
    if (task->output.bb && !APR_BRIGADE_EMPTY(task->output.bb)) {
        /* still have data buffered from previous attempt.
         * setaside and append new data and try to pass the complete data */
        if (!APR_BRIGADE_EMPTY(bb)) {
            status = ap_save_brigade(f, &task->output.bb, &bb, task->pool);
        }
        if (status == APR_SUCCESS) {
            status = send_out(task, task->output.bb, blocking);
        } 
    }
    else {
        /* no data buffered here, try to pass the brigade directly */
        status = send_out(task, bb, blocking); 
        if (status == APR_SUCCESS && !APR_BRIGADE_EMPTY(bb)) {
            /* could not write all, buffer the rest */
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, status, task->c, APLOGNO(03405)
                          "h2_slave_out(%s): saving brigade", 
                          task->id);
            status = ap_save_brigade(f, &task->output.bb, &bb, task->pool);
            flush = 1;
        }
    }
    
    if (status == APR_SUCCESS && !task->output.opened && flush) {
        /* got a flush or could not write all, time to tell someone to read */
        status = open_output(task);
    }
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, task->c, 
                  "h2_slave_out(%s): slave_out leave", task->id);    
    return status;
}

static apr_status_t output_finish(h2_task *task)
{
    if (!task->output.opened) {
        return open_output(task);
    }
    return APR_SUCCESS;
}

/*******************************************************************************
 * task slave connection filters
 ******************************************************************************/

static apr_status_t h2_filter_slave_in(ap_filter_t* f,
                                       apr_bucket_brigade* bb,
                                       ap_input_mode_t mode,
                                       apr_read_type_e block,
                                       apr_off_t readbytes)
{
    h2_task *task;
    apr_status_t status = APR_SUCCESS;
    apr_bucket *b, *next;
    apr_off_t bblen;
    apr_size_t rmax;
    
    task = h2_ctx_cget_task(f->c);
    ap_assert(task);
    rmax = ((readbytes <= APR_SIZE_MAX)? (apr_size_t)readbytes : APR_SIZE_MAX);
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
                  "h2_slave_in(%s): read, mode=%d, block=%d, readbytes=%ld", 
                  task->id, mode, block, (long)readbytes);
    
    if (mode == AP_MODE_INIT) {
        return ap_get_brigade(f->c->input_filters, bb, mode, block, readbytes);
    }
    
    if (f->c->aborted) {
        return APR_ECONNABORTED;
    }
    
    if (!task->input.bb) {
        return APR_EOF;
    }
    
    /* Cleanup brigades from those nasty 0 length non-meta buckets
     * that apr_brigade_split_line() sometimes produces. */
    for (b = APR_BRIGADE_FIRST(task->input.bb);
