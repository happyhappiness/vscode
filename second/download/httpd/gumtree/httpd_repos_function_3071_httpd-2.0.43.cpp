static void run_child_cleanups(cleanup_t *c)
{
    while (c) {
        (*c->child_cleanup_fn)((void *)c->data);
        c = c->next;
    }
}