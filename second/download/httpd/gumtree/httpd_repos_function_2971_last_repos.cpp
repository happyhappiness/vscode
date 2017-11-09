static apr_status_t add_worker(h2_workers *workers)
{
    h2_slot *slot = pop_slot(&workers->free);
    if (slot) {
        return activate_slot(workers, slot);
    }
    return APR_EAGAIN;
}