static void mpm_recycle_completion_context(winnt_conn_ctx_t *context)
{
    /* Recycle the completion context.
     * - clear the ptrans pool
     * - put the context on the queue to be consumed by the accept thread
     * Note:
     * context->accept_socket may be in a disconnected but reusable
     * state so -don't- close it.
     */
    if (context) {
        apr_pool_clear(context->ptrans);
        context->ba = apr_bucket_alloc_create(context->ptrans);
        context->next = NULL;
        ResetEvent(context->overlapped.hEvent);
        apr_thread_mutex_lock(qlock);
        if (qtail) {
            qtail->next = context;
        } else {
            qhead = context;
            SetEvent(qwait_event);
        }
        qtail = context;
        apr_thread_mutex_unlock(qlock);
    }
}