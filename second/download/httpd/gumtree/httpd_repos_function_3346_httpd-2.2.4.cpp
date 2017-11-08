static void *dummy_worker(void *opaque)
{
    apr_thread_t *thd = (apr_thread_t *)opaque;
    TlsSetValue(tls_apr_thread, thd->td);
    return thd->func(thd, thd->data);
}