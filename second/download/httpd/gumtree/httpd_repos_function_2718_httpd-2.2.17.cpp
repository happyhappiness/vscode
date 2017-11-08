apr_status_t apu_dso_mutex_unlock()
{
    return apr_thread_mutex_unlock(mutex);
}