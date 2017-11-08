static int make_child(server_rec *s, int slot)
{
    int tid;
    int err=0;
    NXContext_t ctx;

    if (slot + 1 > ap_max_workers_limit) {
        ap_max_workers_limit = slot + 1;
    }

    ap_update_child_status_from_indexes(0, slot, WORKER_STARTING,
                                        (request_rec *) NULL);

    if (ctx = NXContextAlloc((void (*)(void *)) worker_main, (void*)slot, NX_PRIO_MED, ap_thread_stacksize, NX_CTX_NORMAL, &err)) {
        char threadName[32];

        sprintf (threadName, "Apache_Worker %d", slot);
        NXContextSetName(ctx, threadName);
        err = NXThreadCreate(ctx, NX_THR_BIND_CONTEXT, &tid);
        if (err) {
            NXContextFree (ctx);
        }
    }

    if (err) {
        /* create thread didn't succeed. Fix the scoreboard or else
        * it will say SERVER_STARTING forever and ever
        */
        ap_update_child_status_from_indexes(0, slot, WORKER_DEAD,
                                            (request_rec *) NULL);

        /* In case system resources are maxxed out, we don't want
        Apache running away with the CPU trying to fork over and
        over and over again. */
        apr_thread_yield();

        return -1;
    }

    ap_scoreboard_image->servers[0][slot].tid = tid;

    return 0;
}