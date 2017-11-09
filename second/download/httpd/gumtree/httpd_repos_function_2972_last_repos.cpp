static void wake_idle_worker(h2_workers *workers) 
{
    h2_slot *slot = pop_slot(&workers->idle);
    if (slot) {
        apr_thread_mutex_lock(slot->lock);
        apr_thread_cond_signal(slot->not_idle);
        apr_thread_mutex_unlock(slot->lock);
    }
    else if (workers->dynamic) {
        add_worker(workers);
    }
}