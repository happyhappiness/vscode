apr_os_thread_t apr_os_thread_current()
{
    return NXThreadGetId();
}