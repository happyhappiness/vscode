apr_status_t apu_dso_mutex_lock()
{
    return apr_thread_mutex_lock(mutex);
}