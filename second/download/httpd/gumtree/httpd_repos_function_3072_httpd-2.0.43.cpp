static void cleanup_pool_for_exec(apr_pool_t *p)
{
    run_child_cleanups(p->cleanups);
    p->cleanups = NULL;

    for (p = p->child; p; p = p->sibling)
        cleanup_pool_for_exec(p);
}