static void cleanup_zombies(h2_workers *workers)
{
    h2_slot *slot;
    while ((slot = pop_slot(&workers->zombies))) {
        if (slot->thread) {
            apr_status_t status;
            apr_thread_join(&status, slot->thread);
            slot->thread = NULL;
        }
        apr_atomic_dec32(&workers->worker_count);
        slot->next = NULL;
        push_slot(&workers->free, slot);
    }
}