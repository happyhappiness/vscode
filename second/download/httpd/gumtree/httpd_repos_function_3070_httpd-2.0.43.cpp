static void run_cleanups(cleanup_t *c)
{
    while (c) {
        (*c->plain_cleanup_fn)((void *)c->data);
        c = c->next;
    }
}