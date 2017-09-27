{
    /* XXX If specifying SIG_IGN is guaranteed to unblock a syscall,
     *     then we don't need this goofy function.
     */
}

static void *listener_thread(apr_thread_t *thd, void * dummy)
{
    proc_info * ti = dummy;
    int process_slot = ti->pid;
    apr_pool_t *tpool = apr_thread_pool_get(thd);
    void *csd = NULL;
    apr_pool_t *ptrans = NULL;            /* Pool for per-transaction stuff */
