static h2_fifo_op_t mplx_peek(void *head, void *ctx)
{
    h2_mplx *m = head;
    h2_slot *slot = ctx;
    
    if (slot_pull_task(slot, m) == APR_EAGAIN) {
        wake_idle_worker(slot->workers);
        return H2_FIFO_OP_REPUSH;
    } 
    return H2_FIFO_OP_PULL;
}