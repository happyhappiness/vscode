static void run_cleanups(cleanup_t **cref)
{
    cleanup_t *c = *cref;

    while (c) {
        *cref = c->next;
        (*c->plain_cleanup_fn)((void *)c->data);
        c = *cref;
    }
}