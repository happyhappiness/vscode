static void run_child_cleanups(cleanup_t **cref)
{
    cleanup_t *c = *cref;

    while (c) {
        *cref = c->next;
        (*c->child_cleanup_fn)((void *)c->data);
        c = *cref;
    }
}