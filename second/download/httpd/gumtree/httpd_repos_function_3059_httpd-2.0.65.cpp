static void *dummy_worker(void *opaque)
{
    apr_thread_t *thd = (apr_thread_t *)opaque;
    return thd->func(thd, thd->data);
}