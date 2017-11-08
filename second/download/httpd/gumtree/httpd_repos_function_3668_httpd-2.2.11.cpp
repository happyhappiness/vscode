static void *dummy_worker(void *opaque)
{
    apr_thread_t *thread = (apr_thread_t*)opaque;
    return thread->func(thread, thread->data);
}