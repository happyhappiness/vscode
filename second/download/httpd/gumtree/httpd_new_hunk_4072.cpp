 */

#include <assert.h>

#include <apr_thread_cond.h>

#include <mpm_common.h>
#include <httpd.h>
#include <http_core.h>
#include <http_log.h>

#include "h2.h"
#include "h2_private.h"
#include "h2_conn.h"
#include "h2_ctx.h"
#include "h2_h2.h"
#include "h2_mplx.h"
#include "h2_task.h"
#include "h2_worker.h"

static void* APR_THREAD_FUNC execute(apr_thread_t *thread, void *wctx)
{
    h2_worker *worker = (h2_worker *)wctx;
    int sticky;
    
    while (!worker->aborted) {
        h2_task *task;
        
        /* Get a h2_task from the main workers queue. */
        worker->get_next(worker, worker->ctx, &task, &sticky);
        while (task) {
            h2_task_do(task, worker->io);
            
            /* if someone was waiting on this task, time to wake up */
            apr_thread_cond_signal(worker->io);
            /* report the task done and maybe get another one from the same
             * mplx (= master connection), if we can be sticky. 
             */
            if (sticky && !worker->aborted) {
                h2_mplx_task_done(task->mplx, task, &task);
            }
            else {
                h2_mplx_task_done(task->mplx, task, NULL);
                task = NULL;
            }
        }
    }

    worker->worker_done(worker, worker->ctx);
    return NULL;
}

h2_worker *h2_worker_create(int id,
                            apr_pool_t *parent_pool,
                            apr_threadattr_t *attr,
                            h2_worker_mplx_next_fn *get_next,
                            h2_worker_done_fn *worker_done,
                            void *ctx)
{
    apr_allocator_t *allocator = NULL;
    apr_pool_t *pool = NULL;
    h2_worker *w;
    apr_status_t status;
    
    apr_allocator_create(&allocator);
    apr_allocator_max_free_set(allocator, ap_max_mem_free);
    apr_pool_create_ex(&pool, parent_pool, NULL, allocator);
    apr_pool_tag(pool, "h2_worker");
    apr_allocator_owner_set(allocator, pool);

    w = apr_pcalloc(pool, sizeof(h2_worker));
    if (w) {
        APR_RING_ELEM_INIT(w, link);
        
